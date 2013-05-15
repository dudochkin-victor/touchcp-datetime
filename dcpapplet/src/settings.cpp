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
#include <QtDebug>
#include <QTimer>
#include <MLocale>
#include "timezonemodel.h"
#include "settings.h"

#ifdef HAVE_CELLULAR_QT
#include <networkoperator.h>
#else
#include "cellular-fake.h"
#endif

#ifdef HAVE_QMSYSTEM
#else
#include "qmsystem-fake.h"
#endif

static const int g_TimeUpdateInterval = 1000; /*every second*/
static const char *TimeFormatGConfKey = "/meegotouch/i18n/lc_timeformat24h";
static const char *ClockTypeGConfKey = "/apps/clock/clocktype";

Settings::Settings(QObject* parent):
    QObject(parent),
    m_currentSimStatus(SIMStatus::NoSIM),
    m_TimeFormatGConfItem(0)
{
    m_TimeFormatGConfItem = new MGConfItem(TimeFormatGConfKey);
    m_ClockTypeGConfItem = new MGConfItem(ClockTypeGConfKey);
    connect(m_TimeFormatGConfItem, SIGNAL(valueChanged()),
            this, SIGNAL(datetimeSettingsChanged()));

    connect(m_ClockTypeGConfItem, SIGNAL(valueChanged()),
            this, SIGNAL(datetimeSettingsChanged()));
    
    connect(&m_Time, SIGNAL(timeOrSettingsChanged(MeeGo::QmTimeWhatChanged)),
            this, SLOT(timeOrSettingsChangedSlot(MeeGo::QmTimeWhatChanged)));

    connect(&m_simStatus, SIGNAL(statusChanged (SIMStatus::Status)),
            this, SLOT(onSimStatusChanged (SIMStatus::Status)));

    connect(&m_simStatus, SIGNAL(statusComplete (SIMStatus::Status, SIMError)),
            this, SLOT(onSimStatusChanged (SIMStatus::Status)));

    m_simStatus.status();
    /* init timer for time updates on briefs */
    m_OldTime = QTime::currentTime();
    m_OldDate = QDate::currentDate();
    connect(&m_Timer, SIGNAL(timeout()), this, SLOT(timerTimeoutSlot()));
    displayStateChangedSlot(MeeGo::QmDisplayState::On);
    connect(&m_DisplayState,
            SIGNAL(displayStateChanged(MeeGo::QmDisplayState::DisplayState)),
            this, SLOT(displayStateChangedSlot(MeeGo::QmDisplayState::DisplayState)));
    m_Locale = new MLocale();
    connect(m_Locale, SIGNAL(settingsChanged()), this, SIGNAL(localeChanged()));
    #ifdef SBOX
    m_IsAutoSystemTime = false;
    m_IsAutoTimeZone = false;
    #endif
}

Settings::~Settings()
{
    delete m_TimeFormatGConfItem;
    delete m_ClockTypeGConfItem;
    delete m_Locale; 
}

/* Original declaration of the slot:
 * void Settings::timeOrSettingsChanged(MeeGo::QmTime::WhatChanged what)
 * Some settings may affect time and date. Let treat it as if all may affect,
 * for now.
 */
void Settings::timeOrSettingsChangedSlot(QmTimeWhatChanged what)
{
    switch(what){
        case MeeGo::QmTimeTimeChanged :
            datetimeSettingsChanged();
            emit datetimeChanged();
            break;
        case MeeGo::QmTimeOnlySettingsChanged :
            emit datetimeSettingsChanged();
            break;
        default:
            qCritical("Qmtime returned unknown changed status : %d", what);
            break;
    }
}

Settings& Settings::instance()
{
    static Settings _instance;
    return _instance;
}

void Settings::onSimStatusChanged (SIMStatus::Status status)
{
    m_currentSimStatus = status;
}

bool Settings::cellularNetworkIsAvailable()
{
    Cellular::SystemControl::Status s = m_CellSysCtl.status();
    bool ret = false;
    m_simStatus.status();
    if( m_CellSysCtl.isValid() &&
            ( 
             (s == Cellular::SystemControl::FullService) ||
             (s == Cellular::SystemControl::LimitedService)
            )
      )
        ret = true;
    return ret;
}

bool Settings::autoSystemTime()
{
#ifdef SBOX
    return m_IsAutoSystemTime;
#else
    QmTime::AutoSystemTimeStatus status = m_Time.autoSystemTime();
    if (status == QmTime::AutoSystemTimeUnknown)
	    qWarning() << "There is an error getting auto system time";
    return (status == QmTime::AutoSystemTimeOn);
#endif

}

bool Settings::autoTimeZone()
{
#ifdef SBOX
    return m_IsAutoTimeZone;
#else
    QmTime::AutoTimeZoneStatus status = m_Time.autoTimeZone();
    if (status == QmTime::AutoTimeZoneUnknown)
	    qWarning() << "There is an error getting auto timezone";
    return (status == QmTime::AutoTimeZoneOn);
#endif

}
bool Settings::getAutoSync()
{
    return (cellularNetworkIsAvailable() && autoSystemTime() && autoTimeZone());
}

bool Settings::setAutoSync(bool set)
{
    bool result = setAutoSystemTime(set) && setAutoTimeZone(set);
    if (result)
    	emit datetimeSettingsChanged();
    return result;
}

bool Settings::isSimInserted()
{
    return m_currentSimStatus == SIMStatus::Ok;
}

bool Settings::setAutoSystemTime(bool set)
{

#ifdef SBOX
    m_IsAutoSystemTime = set;
    emit datetimeSettingsChanged();
    return true;
#else
    if(set && !cellularNetworkIsAvailable()){
        qCritical("Cellular network is not available: "
                "could not turn on network time autosync");
        return false;
    }
    QmTime::AutoSystemTimeStatus status = set ? QmTime::AutoSystemTimeOn :
	    QmTime::AutoSystemTimeOff;
    if(m_Time.setAutoSystemTime(status)) {
        bool res = m_Time.autoSystemTime();
        if (res != set) {
            qCritical("QmTime::setAutoSystemTime(%s) returned true but autoSystemTime() returned %s",
                      set ? "true" : "false",
                      res ? "true" : "false");
        }
        return true;
    }

    qCritical("Could not turn %s auto system time",
            (set ? "on" : "off"));
    return false;
#endif
}

bool Settings::setAutoTimeZone(bool set)
{

#ifdef SBOX
    m_IsAutoTimeZone = set;
    emit datetimeSettingsChanged();
    return true;
#else
    if(set && !cellularNetworkIsAvailable()){
        qCritical("Cellular network is not available: "
                "could not turn on auto timezone");
        return false;
    }
    QmTime::AutoTimeZoneStatus status = set ? QmTime::AutoTimeZoneOn :
	    QmTime::AutoTimeZoneOff;
    if(m_Time.setAutoTimeZone(status)) {
        bool res = m_Time.autoTimeZone();
        if (res != set) {
            qCritical("QmTime::setAutoTimeZone(%s) returned true but autoTimeZone() returned %s",
                      set ? "true" : "false",
                      res ? "true" : "false");
        }
        return true;
    }

    qCritical("Could not turn %s auto system time",
            (set ? "on" : "off"));
    return false;
#endif
}
void Settings::getTime(int &hour, int &min) const
{
    QTime time;

    time = QTime::currentTime();

    hour = time.hour();
    min = time.minute();
}

bool Settings::setTime(int hour, int min)
{
    bool ret = true;

    QDateTime newTime;
    newTime.setTime(QTime(hour, min, 0));
    newTime.setDate(QDate::currentDate());

    if(!setDateTime(newTime)){
        qCritical("Could not set time to %s",
                qPrintable(newTime.toString("yyyy/MM/dd - hh:mm")));
        ret = false;
    } else {
        emit timeChanged();
    }
    return ret;
}

void Settings::getDate(int &year, int &month, int &day) const
{
    QDate date;

    date = QDate::currentDate();

    year = date.year();
    month = date.month();
    day = date.day();
}

bool Settings::setDate(int year, int month, int day)
{
    bool ret = true;

    QDateTime newDate;
    newDate.setDate(QDate(year, month, day));
    newDate.setTime(QTime::currentTime());
    if(!setDateTime(newDate)){
        qCritical("Could not set date to %s",
                qPrintable(newDate.toString("yyyy/MM/dd - hh:mm")));
        ret = false;
    } else {
        emit dateChanged();
    }

    return ret;
}

bool Settings::setDateTime(const QDateTime& newDate)
{
    if(getAutoSync())
        setAutoSync(false);

    qDebug("Settings datetime in %s to %s",
            __PRETTY_FUNCTION__,
            qPrintable(newDate.toString("yyyy/MM/dd - hh:mm")));
    return m_Time.setTime(newDate);
}

QString Settings::getTimezone()
{
#ifdef SBOX
    return m_Timezone;
#else

    QString ret;
    if(!m_Time.getTimezone(ret)){
        qCritical("Error during asking QmTime for timezone");
    }
    qDebug("Reported timezone in use: %s", qPrintable(ret));
    return ret;
#endif
}

bool Settings::setTimezone(QString timezone)
{
#ifdef SBOX
    m_Timezone = timezone;
    emit datetimeSettingsChanged();
    return true;
#else
    bool ret;
    if(m_Time.setTimezone(timezone)){
        ret = true;
    } else {
        qCritical() << "Could not set timezone " << timezone;
        ret = false;
    }
    return ret;
#endif
}

/**
 * Returns 12/24h timeformat stored in gconf
 */
TimeFormatId Settings::getTimeFormat()
{
    QString timeFormatStr = m_TimeFormatGConfItem->value().toString();
    if (timeFormatStr == "12") {
        return TimeFormat12h;
    }
    if (timeFormatStr == "24") {
        return TimeFormat24h;
    }
    return TimeFormatLocaleDefault;
}

ClockTypeId Settings::getClockType()
{
    QString clockTypeStr = m_ClockTypeGConfItem->value().toString();
    if (clockTypeStr == "analog") {
        return ClockTypeAnalog;
    }
    if (clockTypeStr == "digital") {
        return ClockTypeDigital;
    }

   return ClockTypeAnalog;
}
/**
 * Locale default timeformat is translated to explicit TimeFormat12h or
 * TimeFormat24h, so it never returns TimeFormatLocaleDefault
 */
TimeFormatId Settings::getEffectiveTimeFormat()
{
    TimeFormatId timeFormat = getTimeFormat();
    if (timeFormat == TimeFormatLocaleDefault) {
        MLocale::TimeFormat24h defaultTimeFormat = m_Locale->defaultTimeFormat24h();
        if (defaultTimeFormat == MLocale::TwelveHourTimeFormat24h) {
            return TimeFormat12h;
        }
        else if (defaultTimeFormat == MLocale::TwentyFourHourTimeFormat24h) {
            return TimeFormat24h;
        } else {
            // invalid value, fallback to 24h
            qWarning("MLocale::defaultTimeFormat24h() returned %d",
                     defaultTimeFormat);
            return TimeFormat24h;            
        }        
    } else {
        return timeFormat;
    }
}

void Settings::setTimeFormat(TimeFormatId id)
{
    switch (id) {
        case TimeFormatLocaleDefault:
            m_TimeFormatGConfItem->set("");
            break;
        case TimeFormat12h:
            m_TimeFormatGConfItem->set("12");
            break;
        case TimeFormat24h:
            m_TimeFormatGConfItem->set("24");
            break;
        default:
            qWarning("invalid timeformat id: %d", id);
    }
}

void Settings::setClockType(ClockTypeId id)
{
    switch (id) {
        case ClockTypeAnalog:
            m_ClockTypeGConfItem->set("analog");
            break;
        case ClockTypeDigital:
            m_ClockTypeGConfItem->set("digital");
            break;
        default:
            qWarning("invalid clock type: %d", id);
    }
}
void Settings::timerTimeoutSlot()
{
    int h,m;
    getTime(h, m);
    if(m_OldTime.hour() != h || m_OldTime.minute() != m){
        m_OldTime.setHMS(h, m, 0);
        timeChanged();

        if(m_OldDate != QDate::currentDate()){
            dateChanged();
            m_OldDate = QDate::currentDate();
        }
    }
}

void Settings::displayStateChangedSlot(
        MeeGo::QmDisplayState::DisplayState state)
{
    if(state == QmDisplayState::On || state == QmDisplayState::Dimmed) {
        if(!m_Timer.isActive())
            m_Timer.start(g_TimeUpdateInterval);
    } else {
        if(m_Timer.isActive())
            m_Timer.stop();
    }
}

