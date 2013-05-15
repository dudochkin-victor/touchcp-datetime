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

#include <QGraphicsLinearLayout>

#include <MApplication>
#include <MApplicationWindow>
#include <MApplicationPage>
#include <MWidget>
#include <MContainer>
#include <MLabel>
#include <MLayout>
#include <MLinearLayoutPolicy>
#include <MGridLayoutPolicy>
#include <MSceneManager>
#include <MStylableWidget>
#include <mwidgetcreator.h>

#ifdef HAVE_DATEPICKER
#include <datepicker.h>
#include <datetimepanel.h>
#else
#include "datepicker-fake.h"
#endif

#include "settings.h"
#include "translation.h"
#include "dateview.h"
#include "titlewidget.h"

#include "debug.h"

M_REGISTER_WIDGET_NO_CREATE (DateView)


DateView::DateView(QGraphicsWidget *parent) : DcpStylableWidget(parent)
{
    m_IsViewCreated = false;
    initWidget();
    QTimer::singleShot(0, this, SLOT(finishView()));
}

DateView::~DateView()
{
}

bool DateView::back()
{
    if(!Settings::instance().setDate(m_Year, m_Month, m_Day)){
        qDebug("Could not set date.");
    }
    return DcpStylableWidget::back();
}

void DateView::retranslateUi()
{
}

bool DateView::isViewCreated()
{
    return m_IsViewCreated;
}

void DateView::initWidget()
{
    QTime t;
    t.start();

    MLayout *layout;

    setObjectName("dateView");

    /* mainLayout */
    layout = new MLayout();
    layout->setContentsMargins(0, 0, 0, 0);

    MGridLayoutPolicy *landscapeLayoutPolicy =
        new MGridLayoutPolicy(layout);
    MLinearLayoutPolicy *portraitLayoutPolicy =
        new MLinearLayoutPolicy(layout, Qt::Vertical);

    portraitLayoutPolicy->setContentsMargins(0, 0, 0, 5);
    landscapeLayoutPolicy->setContentsMargins(0, 0, 0, 0);
    landscapeLayoutPolicy->setSpacing(0);
    portraitLayoutPolicy->setSpacing(0);
    layout->setLandscapePolicy(landscapeLayoutPolicy);
    layout->setPortraitPolicy(portraitLayoutPolicy);
    qDebug("Time elapsed (layout policies): %d ms", t.elapsed());


    /* spacers */
    MStylableWidget* spacer1 = new MStylableWidget();
    spacer1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer1->setStyleName("CommonLargeSpacer");
    portraitLayoutPolicy->addItem (spacer1);
    landscapeLayoutPolicy->addItem(spacer1, 0, 0, 1, 1);
    qDebug("Time elapsed (separator): %d ms", t.elapsed());

    /* title */
    TitleWidget *title = new TitleWidget(qtTrId(QtnCommTimeDatepickerTitle), "CommonLargeHeaderInverted");
    portraitLayoutPolicy->addItem(title);
    landscapeLayoutPolicy->addItem(title, 1, 0, 1, 1);

    /* digital date */
    m_DigitalDate = new DateTimePanel(
            QDateTime::currentDateTime(),
            MLocale::DateShort,
            MLocale::TimeNone);
    m_DigitalDate->setEnabled(false);
    m_DigitalDate->setObjectName("DigitalDate");
    m_DigitalDate->setTimeStyle("sDigitalDate");
    MStylableWidget *container1 = new MStylableWidget();
    QGraphicsLinearLayout *container1Layout = new QGraphicsLinearLayout;
    container1Layout->addItem(m_DigitalDate);
    container1->setLayout(container1Layout);
    container1->setStyleName("cDigitalDate");
    container1->setObjectName("cDigitalDate");
    m_DigitalDate->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    landscapeLayoutPolicy->addItem(container1, 2, 0, 1, 1, Qt::AlignHCenter);
    portraitLayoutPolicy->addItem(container1, Qt::AlignHCenter);

    QGraphicsWidget *spacer2 = new QGraphicsWidget();
    spacer2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    landscapeLayoutPolicy->addItem(spacer2, 3, 0, 1, 1);

    portraitLayoutPolicy->addStretch();
    qDebug("Time elapsed (DigitalTime): %d ms", t.elapsed());

    /* add MonthWidget */
    m_MonthWidget = new DatePicker();
    m_MonthWidget->setObjectName("m_MonthWidget");
    //m_MonthWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    //
    MStylableWidget *container2 = new MStylableWidget();
    QGraphicsLinearLayout *container2Layout = new QGraphicsLinearLayout;
    container2Layout->addItem(m_MonthWidget);
    container2->setLayout(container2Layout);
    container2->setStyleName("cMonthWidget");

    landscapeLayoutPolicy->addItem(container2, 0, 1, 4, 1);
    portraitLayoutPolicy->addItem(container2);
    setLayout(layout);
    qDebug("Time elapsed (MonthWidget): %d ms", t.elapsed());

}

void DateView::finishView()
{
    if (isViewCreated())
        return;

    connect(m_DigitalDate, SIGNAL(timeChanged()),
            this, SLOT(digitalDateChangedSlot()));
    connect(m_MonthWidget, SIGNAL(daySelected(int,int,int)),
            this, SLOT(daySelected(int,int,int)));
    m_MonthWidget->updateContent();
    m_MonthWidget->setEarliestAllowedDay(1970, 1, 1);
    m_MonthWidget->setLatestAllowedDay(2037, 12, 31);
    /* initialize and listen for changes */
    Settings::instance().getDate(m_Year, m_Month, m_Day);
    timeOrDateChangedSlot();
    connect(&Settings::instance(), SIGNAL(datetimeChanged()),
            this, SLOT(timeOrDateChangedSlot()));
    connect(&Settings::instance(), SIGNAL(dateChanged()),
            this, SLOT(timeOrDateChangedSlot()));

    retranslateUi();
    m_IsViewCreated = true;
}

QString DateView::title() const
{
    return QString(qtTrId(QtnCommTimeDatepickerTitle));
}

void DateView::enterDisplayEvent()
{
    /* disable panning */
    MApplicationWindow *win = MApplication::activeApplicationWindow();
    MApplicationPage *page = 0;
    if (win)
        page = win->currentPage();
    if (page)
        page->setPannable(false);
}

void DateView::daySelected(int year, int month, int day)
{
//    bool origBlock = m_DigitalDate->blockSignals(true);
//    bool origBlockMonth = m_MonthWidget->blockSignals(true);

    m_Year = year;
    m_Month = month;
    m_Day = day;
    QDateTime dt = QDateTime::currentDateTime();
    dt.setDate(QDate(year, month, day));
    m_DigitalDate->setTime(dt);

    /* user changed the values, stop update on changes */
    disconnect(&Settings::instance(), SIGNAL(datetimeChanged()),
            this, SLOT(timeOrDateChangedSlot()));
    disconnect(&Settings::instance(), SIGNAL(dateChanged()),
            this, SLOT(timeOrDateChangedSlot()));

//    m_DigitalDate->blockSignals(origBlock);
//    m_DigitalDate->blockSignals(origBlockMonth);
}
void DateView::digitalDateChangedSlot()
{
    bool origBlock = m_MonthWidget->blockSignals(true);

    const QDateTime &dt = m_DigitalDate->time();
    m_Year = dt.date().year();
    m_Month = dt.date().month();
    m_Day = dt.date().day();
    m_MonthWidget->setSelectedDay(m_Year, m_Month, m_Day);
    m_MonthWidget->updateContent();

    /* user changed the values, stop update on changes */
    disconnect(&Settings::instance(), SIGNAL(datetimeChanged()),
            this, SLOT(timeOrDateChangedSlot()));
    disconnect(&Settings::instance(), SIGNAL(dateChanged()),
            this, SLOT(timeOrDateChangedSlot()));

    m_MonthWidget->blockSignals(origBlock);
}

void DateView::timeOrDateChangedSlot()
{
    bool origDigitalBlock = m_DigitalDate->blockSignals(true);
    bool origMonthBlock = m_MonthWidget->blockSignals(true);
    int year, month, day;
    Settings::instance().getDate(year, month, day);
    m_Year = year;
    m_Month = month;
    m_Day = day;
    m_MonthWidget->setSelectedDay(m_Year, m_Month, m_Day);
    m_MonthWidget->updateContent();
    QDateTime dt = QDateTime::currentDateTime();
    dt.setDate(QDate(year, month, day));
    m_DigitalDate->setTime(dt);
    m_DigitalDate->blockSignals(origDigitalBlock);
    m_MonthWidget->blockSignals(origMonthBlock);
}

