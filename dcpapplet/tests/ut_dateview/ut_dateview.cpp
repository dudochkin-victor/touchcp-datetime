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

#include "dateview.h"

#ifdef HAVE_DATEPICKER
#include <datepicker.h>
#include <datetimepanel.h>
#else
#include "datepicker-fake.h"
#endif

#include <settings.h>
#include <MApplication>
#include <MApplicationWindow>
#include <MApplicationPage>
#include <MStylableWidget>
#include "qgraphicswidget-fake.h"
#include "ut_dateview.h"

MStylableWidget::MStylableWidget (QGraphicsItem *)
{
}

void QGraphicsItem::setEnabled (bool)
{

}

#ifdef HAVE_DATEPICKER
DateTimePanel::DateTimePanel(QDateTime const&, MLocale::DateType, MLocale::TimeType)
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

const QDateTime& DateTimePanel::time()
{
    return storedTime;
}
#endif


void Ut_DateView::init()
{
    m_subject = new DateView();
    m_subject->finishView();
    Settings::instance().setDate(2010, 8, 1);
}

void Ut_DateView::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DateView::initTestCase()
{
}

void Ut_DateView::cleanupTestCase()
{
}

void Ut_DateView::testConstruction()
{
    QVERIFY(m_subject);
    QCOMPARE(m_subject->m_Year, 2010);
    QCOMPARE(m_subject->m_Month, 8);
    QCOMPARE(m_subject->m_Day, 1);
}

void Ut_DateView::testBack()
{
    m_subject->m_Year = 2011;
    m_subject->m_Month = 9;
    m_subject->m_Day = 2;
    QVERIFY(m_subject->back());
    int year, month, day;
    Settings::instance().getDate(year, month, day);
    QCOMPARE(year, 2011);
    QCOMPARE(month, 9);
    QCOMPARE(day, 2);
}

void Ut_DateView::testInitWidget()
{
    //QCOMPARE(m_subject->objectName(), QString("dateView"));
    QVERIFY(m_subject->m_DigitalDate);
    //QCOMPARE(m_subject->m_DigitalDate->objectName(), QString("DigitalDate"));
    QVERIFY(m_subject->m_MonthWidget);
    //QCOMPARE(m_subject->m_MonthWidget->objectName(), QString("MonthWidget"));
    
}

void Ut_DateView::testTitle()
{
    QCOMPARE(m_subject->title(), QString("qtn_comm_time_datepicker_title"));
}

void Ut_DateView::testRetranslateUi()
{
    m_subject->retranslateUi(); // it is an empty function
                                // Nothing to test
}

void Ut_DateView::testEnterDisplayEvent()
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

void Ut_DateView::testDaySelected()
{
    m_subject->daySelected(2012, 1,1);
    QDate date = m_subject->m_DigitalDate->time().date();
    QCOMPARE(date.year(), 2012);
    QCOMPARE(date.month(), 1);
    QCOMPARE(date.day(), 1);
}

void Ut_DateView::testTimeOrDateChangedSlot()
{
    Settings &s = Settings::instance();
    s.setDate(2002, 3, 4);
    s.setTime(11,15);
    m_subject->timeOrDateChangedSlot();
    QCOMPARE(m_subject->m_Year, 2002);
    QCOMPARE(m_subject->m_Month, 3);
    QCOMPARE(m_subject->m_Day, 4);
    QDate date = m_subject->m_DigitalDate->time().date();
    QCOMPARE(date.year(), 2002);
    QCOMPARE(date.month(), 3);
    QCOMPARE(date.day(), 4);
}

void Ut_DateView::testDigitalDateChangedSlot()
{
    QDateTime dt = QDateTime::currentDateTime();
    QDate date = dt.date();
    m_subject->m_DigitalDate->setTime(dt);
    m_subject->digitalDateChangedSlot();
    QCOMPARE(m_subject->m_Year, date.year());
    QCOMPARE(m_subject->m_Month, date.month());
    QCOMPARE(m_subject->m_Day, date.day());
}


QTEST_APPLESS_MAIN(Ut_DateView)
