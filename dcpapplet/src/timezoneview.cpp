/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel-datetimeapplet.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/
/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include <QDebug>
#include <QTimer>
#include <QModelIndex>
#include <QItemSelectionModel>
#include <QSortFilterProxyModel>

#include <MList>
#include <MListFilter>
#include <MSortFilterProxyModel>
#include <MLayout>
#include <MLinearLayoutPolicy>
#include <MTextEdit>
#include <MApplication>
#include <MContentItem>
#include <MStylableWidget>

#include "translation.h"
#include "settings.h"
#include "timezonemodel.h"
#include "timezonecell.h"
#include "timezoneview.h"
#include "titlewidget.h"

#define RUNTIME_BACKTRACE_VERBOSE_LEVEL 2
#include "debug.h"

class TimezoneContentItemCreator : public MAbstractCellCreator<TimeZoneCell> {
    public:
        MWidget *createCell(const QModelIndex &index, MWidgetRecycler &recycler) const;
        void updateCell(const QModelIndex& _index, MWidget * cell) 
                const __attribute__ ((no_instrument_function));
        void highlightByText(QString text) {
            highlightText = text;
            highlightText.replace("\\+", "+");
            }
        QString formatText(QString text) const; 
    private:
        QString highlightText;
        friend class Ut_TimeZoneView;

};

MWidget *TimezoneContentItemCreator::createCell(const QModelIndex &index, MWidgetRecycler &recycler) const {
        TimeZoneCell *cell = dynamic_cast<TimeZoneCell*>(recycler.take(TimeZoneCell::staticMetaObject.className()));

        if (cell == NULL) {
            cell = new TimeZoneCell();
            cell->setLayoutPosition(M::CenterPosition);
        }
        updateCell(index, cell);

        return cell;
}

void TimezoneContentItemCreator::updateCell(const QModelIndex& _index, MWidget * cell) const
{
    if(!cell){ /* happens to be null when shortening filter string */
        return;
    }
    if(!_index.isValid()){ /* happens to be invalid when filtered to be empty */
        return;
    }

  Q_ASSERT(cell != NULL);
  Q_ASSERT(cell->metaObject() != NULL);
  Q_ASSERT(cell->metaObject()->className() != NULL);

    TimeZoneCell * contentItem = qobject_cast<TimeZoneCell *>(cell);
    if (!contentItem)
        return;
    QVariant data = _index.data(Qt::DisplayRole);
    QStringList rowData = data.toStringList();
    QString countryName = rowData[TimeZoneModel::Country]; 
    QString cityName = rowData[TimeZoneModel::City];
    QString tmzName =  rowData[TimeZoneModel::Gmt]; 
 
    contentItem->setTitle(formatText(countryName));
    contentItem->setSubtitle(formatText(tmzName) + " " + formatText(cityName));

}
QString TimezoneContentItemCreator::formatText(QString text) const
{
    if (highlightText.isEmpty())
        return text;

    QString result = text;
    int matchingIndex = result.indexOf(highlightText, 0, Qt::CaseInsensitive);
        if(matchingIndex != -1) {
            result.insert(matchingIndex+highlightText.length(), "</b>");
            result.insert(matchingIndex, "<b>");
        }
    return result;
}
TimeZoneView::TimeZoneView(QGraphicsWidget *parent) :
    DcpStylableWidget(parent),
    m_SelectedItem(-1)
{
    m_IsViewCreated = false;
    initWidget();
  //  QTimer::singleShot(0, this, SLOT(finishView()));
    finishView();

}

TimeZoneView::~TimeZoneView()
{
}

bool TimeZoneView::isViewCreated()
{
    return m_IsViewCreated;
}

void TimeZoneView::initWidget()
{
    MLayout *mainLayout = new MLayout(this);
    setLayout(mainLayout);

    MLinearLayoutPolicy *mainLayoutPolicy =
        new MLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayoutPolicy->setStyleName("TimeZoneViewMainLayoutPolicy");

    /* title */
    TitleWidget *title = new TitleWidget(qtTrId(QtnCommSettingsTimeZone), "CommonXLargeHeaderInverted");
    mainLayoutPolicy->addItem(title);

    /* spacers */
    MStylableWidget* spacer1 = new MStylableWidget();
    spacer1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer1->setStyleName("CommonSmallSpacer");
    mainLayoutPolicy->addItem(spacer1);

    m_List = new MList();
    m_List->setObjectName("TimeZoneViewMList");
    m_List->setStyleName("CommonListInverted");
    m_CellCreator = new TimezoneContentItemCreator;
    m_List->setCellCreator(m_CellCreator);
    m_List->setSelectionMode(MList::SingleSelection);
    m_List->setShowGroups(false);
    mainLayoutPolicy->addItem(m_List);

}

void TimeZoneView::finishView()
{
    if (isViewCreated())
        return;
#ifdef TWO_COLUMN_IN_LANDSCAPE
    MWindow *win = MApplication::instance()->activeWindow();
    if(win)
        pageRotated(win->orientation());
    connect(MApplication::activeWindow(),
            SIGNAL(orientationChanged(const M::Orientation &)),
            this, SLOT(pageRotated(const M::Orientation &)));
#endif
    MAbstractItemModel *model = &(TimeZoneModel::instance());
    model->setGrouped(true);
    proxyModel = new MSortFilterProxyModel();
    proxyModel->setSortRole(TimeZoneModel::SortRole);
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterRole(TimeZoneModel::FilterRole);
    proxyModel->setSourceModel(model);
    proxyModel->sort(Qt::AscendingOrder);

    m_List->setItemModel(proxyModel);
    m_List->setShowGroups(true);
    m_List->setIndexVisible(true);
    MListFilter *filter = m_List->filtering();

    filter->setEnabled(true);
    filter->setFilterMode(MListFilter::FilterByApplication);
    filter->setFilterRole(TimeZoneModel::FilterRole);
    filter->editor()->setVisible(false);

    connect(filter, SIGNAL(listPannedUpFromTop()),
            this, SLOT(filteringVKBSlot())); 
    connect(filter->editor(), SIGNAL(textChanged()),
            this, SLOT(liveFilteringTextChangedSlot())); 

    retranslateUi();

    connect(this, SIGNAL(displayEntered()),
            this, SLOT(displayEnteredSlot()));
    connect(m_List, SIGNAL(itemClicked(QModelIndex)),
            this, SLOT(itemClickedSlot(QModelIndex)));
    m_IsViewCreated = true;

}
QString TimeZoneView::title() const
{
    return QString(qtTrId(QtnCommSettingsTimeZone));
}

void TimeZoneView::displayEnteredSlot()
{
    // scrollTo works only in this delayed way
    QTimer::singleShot(1, this, SLOT(scrollToSelected()));
    m_List->setFocus();
}

void TimeZoneView::scrollToSelected()
{
    qDebug("model " + m_IsViewCreated ? "created" : "absent");
    QString tz = Settings::instance().getTimezone();
    qDebug("!!!!!Timezone to scroll to : %s",
            qPrintable(tz));
    QModelIndex sourceIdx = TimeZoneModel::instance().getIndex(tz);

    if (sourceIdx.isValid()) {
        QModelIndex proxyIdx = translateModelIndex(sourceIdx);
        if (!proxyIdx.isValid()) {
            qWarning() << "couldnt translate timezone model index" << sourceIdx.row();
            return;
        }
        QVariant data = proxyIdx.data(Qt::DisplayRole);
        QStringList rowData = data.toStringList();

        qDebug() << rowData[0] << rowData[1] << rowData[2];
        m_List->scrollTo(proxyIdx, MList::PositionAtTopHint);
  
        // temporary disconnect the signal
        disconnect(m_List, SIGNAL(itemClicked(QModelIndex)),            
                   this, SLOT(itemClickedSlot(QModelIndex)));
        m_List->selectItem(proxyIdx);
        connect(m_List, SIGNAL(itemClicked(QModelIndex)),
                this, SLOT(itemClickedSlot(QModelIndex)));
        m_List->setFocus();

    } else {
        qWarning() << "unknown timezone to scroll to:" << tz;
    }
    m_List->setIndexDisplayMode(MList::Floating);
}

void TimeZoneView::liveFilteringTextChangedSlot()
{
    qDebug() << Q_FUNC_INFO;
    // With HWKB live filtering text edit is hidden when empty and shown when user enters text
    if(m_List->filtering()->editor()->text() == "" && m_List->filtering()->editor()->isOnDisplay())
        QTimer::singleShot(1500, this, SLOT(hideEmptyTextEdit()));
    else if(m_List->filtering()->editor()->text() != "" && !m_List->filtering()->editor()->isOnDisplay())
        showTextEdit(true);
 
    QString filter = m_List->filtering()->editor()->text();
    filter.replace("+", "\\+");
    QRegExp::PatternSyntax syntax = QRegExp::RegExp;
    Qt::CaseSensitivity caseSensitivity = Qt::CaseInsensitive;
    QRegExp regExp("^" + filter + "|GMT" + filter + "|\\s" + filter
         , caseSensitivity, syntax);
    
    m_List->filtering()->proxy()->setFilterRegExp(regExp);    
      
       
    m_CellCreator->highlightByText(filter);
    TimeZoneModel *model = qobject_cast<TimeZoneModel*>(m_List->itemModel());
    if (model)
        model->updateData(m_List->firstVisibleItem(),
                          m_List->lastVisibleItem());
}

void TimeZoneView::hideEmptyTextEdit() {
    if(m_List->filtering()->enabled() && m_List->filtering()->editor()->text() == "") {
        showTextEdit(false);
    }
}

void TimeZoneView::filteringVKBSlot()
{
    if(!m_List->filtering()->editor()->isOnDisplay()) {
        showTextEdit(true);
        m_List->filtering()->editor()->setFocus();
    }
}

void TimeZoneView::showTextEdit(bool show) {
    MTextEdit* textEdit = m_List->filtering()->editor();
    MLayout *mlayout = dynamic_cast<MLayout*>(layout());
    MLinearLayoutPolicy *mainLayoutPolicy;
    if (!mlayout) {
        return;
    }

    mainLayoutPolicy = dynamic_cast<MLinearLayoutPolicy*>(mlayout->policy());

    if (mainLayoutPolicy) {
        if (show && !textEdit->isOnDisplay()) {
            textEdit->setVisible(true);
            mainLayoutPolicy->insertItem(1, textEdit);
            m_List->setLayoutPosition(M::TopCenterPosition);
        } else if(textEdit->isOnDisplay()) {
            m_List->setFocus();
            textEdit->setVisible(false);
            mainLayoutPolicy->removeAt(1);
            textEdit->setText("");
        }
    }
}

void TimeZoneView::itemClickedSlot(const QModelIndex &index)
{
    Q_UNUSED(index);
    emit closePage();
}

void TimeZoneView::retranslateUi()
{
}

bool TimeZoneView::back()
{
    
    QItemSelectionModel *selection = m_List->selectionModel();
    QList<QModelIndex> list = selection->selectedIndexes();

    if(list.size()){
        QModelIndex listIdx = list.at(0);
        QVariant data = listIdx.data(Qt::DisplayRole);
        QStringList rowData = data.toStringList();
        QString timezone = rowData[TimeZoneModel::Timezone];

        qDebug("Selected timezone to set: %s",
                qPrintable(timezone));

        if(!Settings::instance().setTimezone(timezone)){
            qWarning("Could not set timezone.");
        }
    }

    return DcpStylableWidget::back();
}

#ifdef TWO_COLUMN_IN_LANDSCAPE
void TimeZoneView::pageRotated(const M::Orientation &orientation)
{
    if(orientation == M::Portrait)
        m_List->setColumns(1);
    else
        m_List->setColumns(2);
    m_List->setViewType("fast");
}
#endif

QModelIndex
TimeZoneView::translateModelIndex(const QModelIndex &timezoneModelIndex)
{
    const QAbstractItemModel *sourceModel = timezoneModelIndex.model();
    QList<const MSortFilterProxyModel *> modelChain;
    const int maxDepth = 3;
    const QAbstractItemModel *m = m_List->itemModel();
    for (int depth = 0; depth < maxDepth; ++depth) {
        if (m == sourceModel) {
            break;
        }
        const MSortFilterProxyModel *proxyModel = 
            qobject_cast<const MSortFilterProxyModel *>(m);
        if (!proxyModel) {
            break;
        }
        modelChain.append(proxyModel);
        m = proxyModel->sourceModel();
    }
    if (m != sourceModel) {
        qWarning() << "original timezone model not found in proxy chain";
        return QModelIndex();
    }

    if (modelChain.isEmpty()) {
        // no proxy models in the way
        return timezoneModelIndex;
    }

    QModelIndex translatedIndex = timezoneModelIndex;
    for (int i = modelChain.count() - 1; i >= 0; --i) {
         const MSortFilterProxyModel *m = modelChain[i];
         translatedIndex = m->mapFromSource(translatedIndex);
    }

    return translatedIndex;
}

