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

#include <QDateTime>
#include <QTimer>

#include <MLocale>
#include <MLabel>
#include <QtGui/QGraphicsLinearLayout>
#include <MButton>
#include <MButtonGroup>
#include <MSceneManager>
#include <MComboBox>
#include <MSeparator>
#include <MStylableWidget>

#include "viewid.h"
#include "timezonemodel.h"

#include "autosyncbutton.h"
#include "translation.h"

#include "debug.h"

#include "drilllistitem.h"
#include "mainview.h"
#include "titlewidget.h"
#include <QDebug>

MainView::MainView(QGraphicsWidget *parent)
    :DcpStylableWidget(parent)
{
    m_IsViewCreated = false;
    initWidget();
    QTimer::singleShot(0, this, SLOT(finishMainView()));
}

MainView::~MainView()
{
}

bool MainView::back()
{
    bool ret = DcpStylableWidget::back();
    refererToChangeWidget(View::None);
    return ret;
}

void MainView::initWidget()
{
    setObjectName("DcpDateTimeAppletMainView");

    /* mainLayoutPolicy */
    QGraphicsLinearLayout *mainLayoutPolicy =
        new QGraphicsLinearLayout(Qt::Vertical);
    setLayout(mainLayoutPolicy);
    mainLayoutPolicy->setSpacing(0);
    mainLayoutPolicy->setContentsMargins(0, 0, 0, 0);

#ifndef MEEGO    
   /* title */
    TitleWidget *title = new TitleWidget(qtTrId(QtnDateTimeTitle), "CommonXLargeHeaderInverted");
    mainLayoutPolicy->addItem(title);
#endif

    /* spacers */
    MStylableWidget* spacer1 = new MStylableWidget();
    spacer1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer1->setStyleName("CommonSmallSpacer");
    mainLayoutPolicy->addItem(spacer1);

    /* m_AutoSyncButton */
    m_AutoSyncButton = new AutoSyncButton();
    m_AutoSyncButton->setObjectName("m_AutoSyncButton");
    m_AutoSyncButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    mainLayoutPolicy->addItem(m_AutoSyncButton);
    
    MStylableWidget* sep1 = new MStylableWidget();
    sep1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    sep1->setStyleName("CommonHeaderDividerInverted");
    mainLayoutPolicy->addItem(sep1);

    /* m_TimeButton */
    m_TimeButton = new DrillListItem();
    m_TimeButton->setObjectName("m_TimeButton");
    mainLayoutPolicy->addItem(m_TimeButton);
    /* m_TimeFormatCBox */
    m_TimeFormatCBox = new MComboBox();
    m_TimeFormatCBox->setObjectName("m_TimeFormatCBox");
    m_TimeFormatCBox->setStyleName("CommonComboBoxInverted");
    mainLayoutPolicy->addItem(m_TimeFormatCBox);

    /* m_ClockTypeCBox */
    m_ClockTypeCBox = new MComboBox();
    m_ClockTypeCBox->setObjectName("m_ClockTypeCBox");
    m_ClockTypeCBox->setStyleName("CommonComboBoxInverted");
    m_ClockTypeCBox->addItem("first placeholder");
    m_ClockTypeCBox->addItem("second placeholder");
    mainLayoutPolicy->addItem(m_ClockTypeCBox);
    /* m_DateButton */
    m_DateButton = new DrillListItem();
    m_DateButton->setObjectName("m_DateButton");
    mainLayoutPolicy->addItem(m_DateButton);

    /* m_TimeZoneButton */
    m_TimeZoneButton = new DrillListItem();
    m_TimeZoneButton->setObjectName("m_TimeZoneButton");
    mainLayoutPolicy->addItem(m_TimeZoneButton);

    MStylableWidget* sep2 = new MStylableWidget();
    sep2->setStyleName("CommonSmallSpacer");
    mainLayoutPolicy->addItem(sep2);
    mainLayoutPolicy->addStretch();
    m_Locale = MLocale::createSystemMLocale();
    m_Locale->connectSettings();
    connect(m_Locale, SIGNAL(settingsChanged()),
            this, SLOT(mlocaleSettingsChanged()));
 
}

void MainView::finishMainView()
{
    if(isViewCreated())
       return;

    m_TimeFormatCBox->addItem("first placeholder");
    m_TimeFormatCBox->addItem("second placeholder");
    connect(m_TimeButton, SIGNAL(clicked()), this, SLOT(showTimeView()));
    connect(m_DateButton, SIGNAL(clicked()), this, SLOT(showDateView()));
    connect(m_TimeFormatCBox, SIGNAL(activated(int)),
            this, SLOT(timeFormatCBoxActivatedSlot(int)));
    connect(m_ClockTypeCBox, SIGNAL(activated(int)),
            this, SLOT(clockTypeCBoxActivatedSlot(int)));
    connect(m_TimeZoneButton, SIGNAL(clicked()), this, SLOT(showTimeZoneView()));
    retranslateUi();

    Settings &set = Settings::instance();
    connect(&set, SIGNAL(timeChanged()), this, SLOT(updateTimeText()));
    connect(&set, SIGNAL(dateChanged()), this, SLOT(updateDateText()));
    connect(&set, SIGNAL(datetimeChanged()), this, SLOT(datetimeChangedSlot()));
    connect(&set, SIGNAL(datetimeSettingsChanged()),
            this, SLOT(datetimeSettingsChangedSlot()));

    // init values and dimming state
    datetimeSettingsChangedSlot();

    m_IsViewCreated = true;
}

bool MainView::isViewCreated()
{
    return m_IsViewCreated;
}

QString MainView::title() const
{
    return QString(qtTrId(QtnDateTimeTitle));
}

void MainView::retranslateUi()
{
    updateTimeText();
    updateDateText();
    updateTimeZoneText();
    updateTimeFormatText();
    updateClockTypeText();
}

void MainView::updateTimeText()
{
    qDebug() << Q_FUNC_INFO;
/*
    MLocale * locale = MLocale::createSystem;
    TimeFormatId timeFormat = Settings::instance().getEffectiveTimeFormat();
    switch (timeFormat) {
        case TimeFormat12h:
            qDebug() << "12h";
            locale.setTimeFormat24h(MLocale::TwelveHourTimeFormat24h);
	    break;
        case TimeFormat24h:
            qDebug() << "24h";
            locale.setTimeFormat24h(MLocale::TwentyFourHourTimeFormat24h);
            break;
	default:
	    qDebug() << "Timeformat is not detected";
    }
*/
    QDateTime dateTime = QDateTime::currentDateTime();    
    QString text = m_Locale->formatDateTime(dateTime, MLocale::DateNone,
                                        MLocale::TimeShort);
    setupItem(m_TimeButton, qtTrId(QtnCommSettingsTime), text);
}

void MainView::setupItem(DrillListItem *item, QString title, QString subtitle)
{
//  if (!item->isEnabled())
//  {
//      title = "<i>" + title + "</i>";
//      subtitle = "<i>" + subtitle + "</i>";
//  }
    item->setTitle(title);
    item->setSubtitle(subtitle);
    
}

void MainView::updateDateText()
{
    QDateTime date = QDateTime::currentDateTime();
    QString text = m_Locale->formatDateTime(date, MLocale::DateFull,
                                            MLocale::TimeNone);
    if (!text.isEmpty())
        text.replace(0, 1, text[0].toUpper());
    setupItem(m_DateButton, qtTrId(QtnCommSettingsDate), text);
}

void MainView::updateTimeZoneText()
{
    QString timezone = Settings::instance().getTimezone();
    QString tmzText = "";
    const QString gmt = TimeZoneModel::instance().toGmt(timezone);
    if (!timezone.isEmpty())
        tmzText = gmt + " " +
            TimeZoneModel::instance().tmzCity(timezone);
    else
      tmzText = "(unset)";
    setupItem(m_TimeZoneButton, qtTrId(QtnCommSettingsTimeZone), tmzText);
}

void MainView::updateTimeFormatText()
{
    QString text;

    /* The TimeFormatId enum has two item with 0 and 1 values which are nice as
     * indexes for the combo box. */
    m_TimeFormatCBox->setTitle(qtTrId(QtnDateTimeFormat));

    text = qtTrId(QtnCommTimeFormat12);
    text.replace("%L1", m_Locale->formatNumber(12));
    m_TimeFormatCBox->setItemText(TimeFormatCBoxIndex12h, text);

    text = qtTrId(QtnCommTimeFormat24);
    text.replace("%L1", m_Locale->formatNumber(24));
    m_TimeFormatCBox->setItemText(TimeFormatCBoxIndex24h, text);

    TimeFormatId timeFormat = Settings::instance().getEffectiveTimeFormat();
    switch (timeFormat) {
        case TimeFormat12h:
            m_TimeFormatCBox->setCurrentIndex(TimeFormatCBoxIndex12h);
            break;
        case TimeFormat24h:
            m_TimeFormatCBox->setCurrentIndex(TimeFormatCBoxIndex24h);
            break;
        default:
            // invalid value, it should not happen
            m_TimeFormatCBox->setCurrentIndex(TimeFormatCBoxIndexInvalid);
    }
}

void MainView::updateClockTypeText()
{
    m_ClockTypeCBox->setTitle(qtTrId(QtnDateClockType));

    m_ClockTypeCBox->setItemText(ClockTypeCBoxIndexAnalog,
         qtTrId(QtnDateClockTypeAnalog));
    
    m_ClockTypeCBox->setItemText(ClockTypeCBoxIndexDigital,
         qtTrId(QtnDateClockTypeDigital));
    ClockTypeId clockType = Settings::instance().getClockType();
    switch (clockType) {
        case ClockTypeAnalog:
            m_ClockTypeCBox->setCurrentIndex(ClockTypeCBoxIndexAnalog);
            break;
        case ClockTypeDigital:
            m_ClockTypeCBox->setCurrentIndex(ClockTypeCBoxIndexDigital);
            break;
        default:
            // invalid value, it should not happen
            m_ClockTypeCBox->setCurrentIndex(ClockTypeCBoxIndexInvalid);
    }

}

void MainView::showDateView()
{
    refererToChangeWidget(View::Main);
    emit changeWidget(View::Date);
}

void MainView::showTimeView()
{
    qDebug("m_TimeButton enabled: %d", m_TimeButton->isEnabled());
    refererToChangeWidget(View::Main);
    emit changeWidget(View::Time);
}

void MainView::showTimeZoneView()
{
    refererToChangeWidget(View::Main);
    emit changeWidget(View::TimeZone);
}

void MainView::datetimeChangedSlot()
{
    updateTimeText();
    updateDateText();
}

void MainView::datetimeSettingsChangedSlot()
{
    datetimeChangedSlot();
    updateTimeZoneText();
    updateTimeFormatText();
    bool autoSyncEnabled = Settings::instance().getAutoSync();
    m_TimeButton->setDisabled(autoSyncEnabled);
    m_DateButton->setDisabled(autoSyncEnabled);
    m_TimeZoneButton->setDisabled(autoSyncEnabled);
}

void MainView::timeFormatCBoxActivatedSlot(int idx)
{
    qDebug() << Q_FUNC_INFO;
 //   m_Locale->connectSettings();
    Settings::instance().setTimeFormat(
            (idx == TimeFormatCBoxIndex12h) ? TimeFormat12h : TimeFormat24h);
   if (m_Locale)
	delete m_Locale;
    m_Locale = MLocale::createSystemMLocale();
    updateTimeText();
}

void MainView::clockTypeCBoxActivatedSlot(int idx)
{
    Settings::instance().setClockType(
            (idx == ClockTypeCBoxIndexAnalog) ? ClockTypeAnalog : ClockTypeDigital);
}

void MainView::mlocaleSettingsChanged()
{
    /* if locale specific settings are changed update everything */
    qDebug("mlocale settings changed");
    datetimeSettingsChangedSlot();
}

