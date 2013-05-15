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
#include <QSignalSpy>

#include <settings.h>


#include "ut_settings.h"
#include "../doubles/systemcontroldata.h"

void Ut_Settings::init()
{
}

void Ut_Settings::cleanup()
{
}

void Ut_Settings::initTestCase()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_Settings::cleanupTestCase()
{
}

void Ut_Settings::testInstance()
{
    Settings &s = Settings::instance();
    QVERIFY(&s == &(Settings::instance()));
    QVERIFY(s.m_OldTime.isValid());
    QVERIFY(s.m_OldDate.isValid());
    
}

void Ut_Settings::testCellularNetworkIsAvailable()
{
    setSysControlIsValid(true);
    Settings &s = Settings::instance();
    setSysControlStatus(Cellular::SystemControl::FullService);
    QVERIFY(s.cellularNetworkIsAvailable());
    setSysControlStatus(Cellular::SystemControl::LimitedService);
    QVERIFY(s.cellularNetworkIsAvailable());
    
    setSysControlStatus(Cellular::SystemControl::UnknownStatus);
    QVERIFY(!s.cellularNetworkIsAvailable());
    setSysControlStatus(Cellular::SystemControl::NoService);
    QVERIFY(!s.cellularNetworkIsAvailable());
    setSysControlStatus(Cellular::SystemControl::ModemFailure);
    QVERIFY(!s.cellularNetworkIsAvailable());
}

void Ut_Settings::testAutoSync()
{
	/*
    Settings &s = Settings::instance();
    setSysControlStatus(Cellular::SystemControl::FullService);
    s.setAutoSync(true);
    QVERIFY(s.m_Time.autoSystemTime() == MeeGo::QmTime::AutoSystemTimeOn);
    QVERIFY(s.m_Time.autoTimeZone() == MeeGo::QmTime::AutoTimeZoneOn);
    s.m_Time.setAutosync(false);
    QVERIFY(!s.getAutoSync());
    QVERIFY(s.m_Time.autoSystemTime() == MeeGo::QmTime::AutoSystemTimeOff);
    QVERIFY(s.m_Time.autoTimeZone() == MeeGo::QmTime::AutoTimeZoneOff);
    s.m_Time.setAutosync(true);
    QVERIFY(s.getAutoSync());
    setSysControlStatus(Cellular::SystemControl::NoService);
    QVERIFY(!s.setAutoSync(true));
*/
    }

void Ut_Settings::testTime()
{
    int hour=0, min=0;
    Settings &s = Settings::instance();
    QTime now, result;
    now = QTime::currentTime();
    s.getTime(hour, min);
    result = QTime(hour, min);
    QVERIFY(result.isValid());  
    QVERIFY(now.msecsTo(result) < 60); 

    QSignalSpy spy(&s, SIGNAL(timeChanged()));
    QVERIFY(s.setTime(10, 15));
    QCOMPARE(spy.count(), 1);
 
}

void Ut_Settings::testDate()
{
    int year=0;
    int month=0;
    int day=0;
    QDate result, now;
    Settings &s = Settings::instance();
    s.getDate(year, month, day);
    result.setDate(year, month, day);
    QVERIFY(result.isValid());  
    
    now = QDate::currentDate();
    
    QVERIFY(result.toJulianDay() - now.toJulianDay() == 0 ||
            result.toJulianDay() - now.toJulianDay() == 1);

    QSignalSpy spy(&s, SIGNAL(dateChanged()));
    QVERIFY(s.setDate(2008, 10, 31));
    QCOMPARE(spy.count(), 1);
}

void Ut_Settings::testDateTime()
{
    Settings &s = Settings::instance();
    QDateTime now = QDateTime::currentDateTime();
    QVERIFY(s.setDateTime(now));
}

void Ut_Settings::testTimezone()
{
    Settings &s = Settings::instance();
    s.setTimezone("Europe/Helsinki");
    QString tz;
    s.m_Time.getTimezone(tz);
    QCOMPARE(tz, QString("Europe/Helsinki"));
    QCOMPARE(s.getTimezone(), QString("Europe/Helsinki"));
}

void Ut_Settings::testTimeFormat()
{
    Settings &s = Settings::instance();
    s.setTimeFormat(TimeFormat12h);
    QVERIFY(s.m_TimeFormatGConfItem->value().toString() == "12");
    s.setTimeFormat(TimeFormat24h);
    QVERIFY(s.m_TimeFormatGConfItem->value().toString() == "24");
    s.setTimeFormat(TimeFormatLocaleDefault);
    QVERIFY(s.m_TimeFormatGConfItem->value().toString() == "");
    
    s.m_TimeFormatGConfItem->set("12");
    QVERIFY(s.getTimeFormat() == TimeFormat12h);
    QVERIFY(s.getEffectiveTimeFormat() == TimeFormat12h);
    s.m_TimeFormatGConfItem->set("24");
    QVERIFY(s.getTimeFormat() == TimeFormat24h);
    QVERIFY(s.getEffectiveTimeFormat() == TimeFormat24h);
    s.m_TimeFormatGConfItem->set("");
    QVERIFY(s.getTimeFormat() == TimeFormatLocaleDefault);
    QVERIFY(s.getEffectiveTimeFormat() == TimeFormat24h ||
            s.getEffectiveTimeFormat() == TimeFormat12h);
}

void Ut_Settings::testTimeOrSettingsChangedSlot()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_Settings::testTimerTimeoutSlot()
{
    Settings &s = Settings::instance();
    QTime timeNow = QTime::currentTime();
    QDate dateNow = QDate::currentDate();
    s.m_OldTime.setHMS(0, 0, 0);
    s.m_OldDate.fromJulianDay(0);
    s.timerTimeoutSlot();
    QVERIFY(timeNow.msecsTo(s.m_OldTime) < 60); 
    QVERIFY(s.m_OldDate.toJulianDay() - dateNow.toJulianDay() == 0 ||
            s.m_OldDate.toJulianDay() - dateNow.toJulianDay() == 1);
}

void Ut_Settings::testDisplayStateChangedSlot()
{
    
    Settings &s = Settings::instance();
    s.m_Timer.stop();
    s.displayStateChangedSlot(QmDisplayState::On);
    QVERIFY(s.m_Timer.isActive());
    s.m_Timer.stop();
    s.displayStateChangedSlot(QmDisplayState::Dimmed);
    QVERIFY(s.m_Timer.isActive());
    s.displayStateChangedSlot(QmDisplayState::Off);
    QVERIFY(!s.m_Timer.isActive());
    s.m_Timer.start();
    s.displayStateChangedSlot(QmDisplayState::Unknown);
    QVERIFY(!s.m_Timer.isActive());
}

QTEST_APPLESS_MAIN(Ut_Settings)
