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

#include <MApplication>
#include <MApplicationWindow>
#include <MApplicationPage>
#include <MLayout>
#include <MLinearLayoutPolicy>
#include <MGridLayoutPolicy>
#include <MWidget>
#include <MLabel>
#include <MSceneManager>
#include <MContainer>
#include <QGraphicsLinearLayout>
#include <MStylableWidget>
#include <QDebug>

#include "translation.h"
#include "settings.h"
#include "timeview.h"
#include "titlewidget.h"
#include <QDebug>
#ifdef HAVE_TIMEPICKER
#include <timepicker.h>
#else
#include "timepicker-fake.h"
#endif

#ifdef HAVE_DATEPICKER
#include <datetimepanel.h>
#else
#include "datepicker-fake.h"
#endif
#include <mwidgetcreator.h>

M_REGISTER_WIDGET_NO_CREATE (TimeView)

TimeView::TimeView(QGraphicsWidget *parent) : DcpStylableWidget(parent),
        m_BlockInfiniteTimeChangeLoop(false)
{
    m_IsViewCreated = false;
    initWidget();
    QTimer::singleShot(0, this, SLOT(finishView()));
}

bool TimeView::back()
{
   qDebug() << "Time from timepicker is" << m_TimePicker->hours() << m_TimePicker->minutes();
   if(!Settings::instance().setTime(m_TimePicker->hours(), m_TimePicker->minutes())){
        qWarning("Could not set time.");
    }
    return DcpStylableWidget::back();
}

void TimeView::initWidget()
{
    MLayout *layout;
    setObjectName("timeView");

    /* mainLayout */
    layout = new MLayout();
    setLayout(layout);

    MGridLayoutPolicy *landscapeLayoutPolicy =
        new MGridLayoutPolicy(layout);
    MLinearLayoutPolicy *portraitLayoutPolicy =
        new MLinearLayoutPolicy(layout, Qt::Vertical);

    portraitLayoutPolicy->setContentsMargins(0, 0, 0, 60);
    landscapeLayoutPolicy->setContentsMargins(0, 0, 0, 0);
    layout->setLandscapePolicy(landscapeLayoutPolicy);
    layout->setPortraitPolicy(portraitLayoutPolicy);


    /* spacers */
    MStylableWidget* spacer1 = new MStylableWidget();
    spacer1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer1->setStyleName("CommonLargeSpacer");
    portraitLayoutPolicy->addItem (spacer1);
    landscapeLayoutPolicy->addItem(spacer1, 0, 0, 1, 1);

    /* title */
    TitleWidget *title = new TitleWidget(qtTrId(QtnCommTimeTimepickerTitle), "CommonLargeHeaderInverted");
    portraitLayoutPolicy->addItem(title);
    landscapeLayoutPolicy->addItem(title, 1, 0, 1, 1);


    /* digital time */
    //if (m_DigitalTime)
//	delete m_DigitalTime;
    m_DigitalTime = new DateTimePanel(
            QDateTime::currentDateTime(),
            MLocale::DateNone,
            MLocale::TimeShort);
    qDebug() << "DateTimePanel has created";
    m_DigitalTime->setEnabled(true);
    m_DigitalTime->setObjectName("DigitalTime");
    m_DigitalTime->setTimeStyle("sDigitalTime");
    m_DigitalTime->setAmStyle("CommonSingleButtonInverted");
    m_DigitalTime->setPmStyle("CommonSingleButtonInverted");
    
    MStylableWidget *container1 = new MStylableWidget();
    QGraphicsLinearLayout *container1Layout = new QGraphicsLinearLayout;
    container1Layout->addItem(m_DigitalTime);
    container1->setLayout(container1Layout);
    container1->setStyleName("cDigitalTime");
    container1->setObjectName("cDigitalTime");

    m_DigitalTime->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
   // m_DigitalTime->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    landscapeLayoutPolicy->addItem(container1, 2, 0, 1, 1, Qt::AlignHCenter);
    portraitLayoutPolicy->addItem(container1, Qt::AlignHCenter);
    //portraitLayoutPolicy->addItem(m_DigitalTime);
   // portraitLayoutPolicy->setAlignment(m_DigitalTime, Qt::AlignCenter);
   // landscapeLayoutPolicy->addItem(m_DigitalTime, 2, 0, 1, 1);
    //landscapeLayoutPolicy->setAlignment(m_DigitalTime, Qt::AlignCenter);

    /* analogClock */
    MWidget *timePickerWidget = new MWidget();
    QGraphicsLinearLayout *timePickerLayout = new QGraphicsLinearLayout();
    timePickerLayout->setContentsMargins(0, 0, 0, 0);
    timePickerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    timePickerWidget->setLayout(timePickerLayout);

    m_TimePicker = new TimePicker();
    m_TimePicker->setObjectName("TimePicker");
    m_TimePicker->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    timePickerLayout->addItem(m_TimePicker);
    timePickerLayout->setAlignment(m_TimePicker, Qt::AlignCenter);

    QGraphicsWidget *spacer3 = new QGraphicsWidget();
    spacer3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    portraitLayoutPolicy->addStretch();
    portraitLayoutPolicy->addItem(timePickerWidget, Qt::AlignHCenter | Qt::AlignBottom);
    landscapeLayoutPolicy->addItem(spacer3, 3, 0, 1, 1);
    landscapeLayoutPolicy->addItem(timePickerWidget, 0, 1, 4, 1, Qt::AlignCenter);

    landscapeLayoutPolicy->setColumnFixedWidth(1, 432);

}

void TimeView::finishView()
{
    if (isViewCreated())
        return;
    connect(m_DigitalTime, SIGNAL(timeChanged()),
            this, SLOT(digitalTimeChangedSlot()));
    m_DigitalTime->setEnabled(true);
    
    connect(m_TimePicker, SIGNAL(timeChanged(int, int)),
            this, SLOT(pickerTimeChangedSlot(int, int)));
    /* initialize and listen for changes */
    timeOrDateChangedSlot();
    connect(&Settings::instance(), SIGNAL(datetimeChanged()),
            this, SLOT(timeOrDateChangedSlot()));
    connect(&Settings::instance(), SIGNAL(timeChanged()),
            this, SLOT(timeOrDateChangedSlot()));

    retranslateUi();
    m_IsViewCreated = true;

}

bool TimeView::isViewCreated()
{
    return m_IsViewCreated;
}

QString TimeView::title() const
{
    return QString(qtTrId(QtnCommTimeTimepickerTitle));
}

void TimeView::enterDisplayEvent()
{
    /* disable panning */
    MApplicationWindow *win = MApplication::activeApplicationWindow();
    MApplicationPage *page = 0;
    if (win)
        page = win->currentPage();
    if (page)
        page->setPannable(false);
}

void TimeView::retranslateUi()
{
}

void TimeView::pickerTimeChangedSlot(int hour, int min)
{
    if(m_BlockInfiniteTimeChangeLoop)
        return;
    m_BlockInfiniteTimeChangeLoop = true;

    QDateTime dt = QDateTime::currentDateTime();
    dt.setTime(QTime(hour, min));
    m_DigitalTime->setTime(dt);

    /* user changed the values, stop update on changes */
    disconnect(&Settings::instance(), SIGNAL(datetimeChanged()),
            this, SLOT(timeOrDateChangedSlot()));
    disconnect(&Settings::instance(), SIGNAL(timeChanged()),
            this, SLOT(timeOrDateChangedSlot()));

    m_BlockInfiniteTimeChangeLoop = false;
}

void TimeView::digitalTimeChangedSlot()
{
    if(m_BlockInfiniteTimeChangeLoop)
        return;
    m_BlockInfiniteTimeChangeLoop = true;

    const QDateTime &dt = m_DigitalTime->time();
    m_TimePicker->setHours(dt.time().hour());
    m_TimePicker->setMinutes(dt.time().minute());

    /* user changed the values, stop update on changes */
    disconnect(&Settings::instance(), SIGNAL(datetimeChanged()),
            this, SLOT(timeOrDateChangedSlot()));
    disconnect(&Settings::instance(), SIGNAL(timeChanged()),
            this, SLOT(timeOrDateChangedSlot()));

    m_BlockInfiniteTimeChangeLoop = false;
}

void TimeView::timeOrDateChangedSlot()
{
    m_BlockInfiniteTimeChangeLoop = true;

    int hour, min;
    Settings::instance().getTime(hour, min);
    m_TimePicker->setHours(hour);
    m_TimePicker->setMinutes(min);
    QDateTime dt = QDateTime::currentDateTime();
    dt.setTime(QTime(hour, min));
    m_DigitalTime->setTime(dt);
    
    m_BlockInfiniteTimeChangeLoop = false;
}

