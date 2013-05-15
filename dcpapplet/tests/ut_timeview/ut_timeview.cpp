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

#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <MStylableWidget>

#include <timeview.h>
#ifdef HAVE_DATEPICKER
#include <datetimepanel.h>
#include <timepicker.h>
#else
#include "datepicker-fake.h"
#include "timepicker-fake.h"
#endif

#include <settings.h>
#include <MApplication>
#include <MApplicationWindow>
#include <MApplicationPage>
#include "qgraphicswidget-fake.h"
#include "ut_timeview.h"

MStylableWidget::MStylableWidget (QGraphicsItem *)
{
}

#ifdef HAVE_DATEPICKER
DateTimePanel::DateTimePanel(QDateTime const&, MLocale::DateType, MLocale::TimeType)
{

}

void QGraphicsItem::setEnabled (bool)
{

}


static QDateTime storedTime;
void DateTimePanel::setTime(QDateTime const &newtime)
{
    storedTime = newtime;
}

void DateTimePanel::setTimeStyle(const QString)
{
}

void DateTimePanel::setAmStyle(const QString)
{
}

void DateTimePanel::setPmStyle(const QString)
{
}

const QDateTime& DateTimePanel::time()
{
    return storedTime;
}
#endif

void Ut_TimeView::init()
{
    m_subject = new TimeView();
    m_subject->finishView();
}

void Ut_TimeView::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_TimeView::initTestCase()
{
}

void Ut_TimeView::cleanupTestCase()
{
}

void Ut_TimeView::testConstruction()
{
    QVERIFY(m_subject);
    QVERIFY(!m_subject->m_BlockInfiniteTimeChangeLoop);
}

void Ut_TimeView::testBack()
{
#ifndef HAVE_TIMEPICKER
    QSKIP("Timepicker needed", SkipSingle);
#endif
    Settings &s = Settings::instance();
    s.setTime(0, 0);
    m_subject->m_TimePicker->setHours(10);
    m_subject->m_TimePicker->setMinutes(15);
    QVERIFY(m_subject->back());
    int hour, min;
    s.getTime(hour, min);
    QCOMPARE(hour, 10);
    QCOMPARE(min, 15);
}

void Ut_TimeView::testPagePans()
{
    QVERIFY(!m_subject->pagePans());
}
void Ut_TimeView::testInitWidget()
{
    //QCOMPARE(m_subject->objectName(), QString("timeView"));
    QVERIFY(m_subject->m_DigitalTime);
    QVERIFY(m_subject->m_TimePicker);
    
}

void Ut_TimeView::testTitle()
{
    QCOMPARE(m_subject->title(), QString("qtn_comm_time_timepicker_title"));
}

void Ut_TimeView::testRetranslateUi()
{
    m_subject->retranslateUi(); // it is an empty function
                                // Nothing to test
}

void Ut_TimeView::testEnterDisplayEvent()
{
/*
    MApplicationWindow *win = MApplication::activeApplicationWindow();
    MApplicationPage *page = win->currentPage();
    
    QVERIFY(page->isPannable());
    m_subject->enterDisplayEvent();
    QVERIFY(!page->isPannable());
    */
    QSKIP("not supported by mgt", SkipSingle);
}

void Ut_TimeView::testDigitalTimeChangedSlot()
{
#ifndef HAVE_TIMEPICKER
    QSKIP("Timepicker needed", SkipSingle);
#endif
    m_subject->m_TimePicker->setHours(8);
    m_subject->m_TimePicker->setMinutes(30);
    QDateTime dt = QDateTime::currentDateTime();
    dt.setTime(QTime(12, 45));
    QDateTime result;
    m_subject->m_DigitalTime->setTime(dt);
    m_subject->digitalTimeChangedSlot();
    QCOMPARE(m_subject->m_TimePicker->hours(), 12); 
    QCOMPARE(m_subject->m_TimePicker->minutes(), 45); 
}

void Ut_TimeView::testTimeOrDateChangedSlot()
{
#ifndef HAVE_TIMEPICKER
    QSKIP("Timepicker needed", SkipSingle);
#endif
    Settings &s = Settings::instance();
    s.setTime(11, 20);
    m_subject->timeOrDateChangedSlot();
    QCOMPARE(m_subject->m_TimePicker->hours(), 11);
    QCOMPARE(m_subject->m_TimePicker->minutes(), 20);
    QDateTime result = m_subject->m_DigitalTime->time();
    QCOMPARE(result.time().hour(), 11);
    QCOMPARE(result.time().minute(), 20);
}

void Ut_TimeView::testPickerTimeChangedSlot()
{
    QDateTime dt = QDateTime::currentDateTime();
    dt.setTime(QTime(0, 0));
    QDateTime result;
    m_subject->m_DigitalTime->setTime(dt);
    m_subject->m_BlockInfiniteTimeChangeLoop = true;
    m_subject->pickerTimeChangedSlot(10, 15);
    // no changes are expected
    result = m_subject->m_DigitalTime->time();
    QCOMPARE(result.time().hour(), 0);
    QCOMPARE(result.time().minute(), 0);
    m_subject->m_BlockInfiniteTimeChangeLoop = false;
    // changing time in DigitalTime edit
    m_subject->pickerTimeChangedSlot(10, 15);
    result = m_subject->m_DigitalTime->time();
    QCOMPARE(result.time().hour(), 10);
    QCOMPARE(result.time().minute(), 15);
    
}


QTEST_APPLESS_MAIN(Ut_TimeView)
