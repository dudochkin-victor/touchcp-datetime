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

#ifndef QMSYSTEMFAKE_H
#ifdef HAVE_QMSYSTEM
#include <qmtime.h>
#else
#include "qmsystem-fake.h"
#endif

namespace MeeGo {


#ifdef HAVE_QMSYSTEM
QmTime::TimeFormat s_TimeFormat;
bool s_setTimeFormat = false;
#endif

QString s_TimezoneName = "";
bool s_getTimezone = false;
bool s_setTimezone = false;

bool s_AutoSync = false;
bool s_setAutoSync = false;

QmTime::AutoSystemTimeStatus s_AutoSystemTime = QmTime::AutoSystemTimeUnknown;
bool s_setAutoSystemTime = false;

QmTime::AutoTimeZoneStatus s_AutoTimeZone = QmTime::AutoTimeZoneUnknown;
bool s_setAutoTimeZone = false;

QDateTime s_DateTime;



QmTime::QmTime(QObject *parent) :
#ifdef HAVE_QMSYSTEM
    QObject(parent),
    priv_ptr(0)
#else
    QObject(parent)
#endif
{
}

QmTime::~QmTime()
{
}

/*bool QmTime::getNetTime(QDateTime& time, QString& tz)
  {
  if(mockret_getNetTime){
  tz = m_TZName;
  time = m_DateTime;
  }
  return m_getNetTime;
  }
  */

bool QmTime::setTime(const QDateTime& time)
{
    if(time.isValid()){
        s_DateTime = time;
        //emit_timeOrSettingsChanged(MeeGo::QmTimeTimeChanged);
        return true;
    }
    return false;
}

bool QmTime::getTimezone(QString& s)
{
    s = s_TimezoneName;
    return true;
}
/*
bool QmTime::getTZName(QString& s)
{
    Q_UNUSED(s);
    return false;
}
*/
bool QmTime::setTimezone(const QString tz)
{
    s_TimezoneName = tz;
    return true;
}

#ifdef HAVE_QMSYSTEM
/*
   bool QmTime::getRemoteTime(const QDateTime& time, const QString& tz, QDateTime& remoteTime)
   */
QmTime::TimeFormat QmTime::getTimeFormat()
{
    return s_TimeFormat;
}

bool QmTime::setTimeFormat(QmTime::TimeFormat format)
{
    s_TimeFormat = format;
    return true;
}
/*
int QmTime::getUTCOffset(const QString& tz)
{
    return s_UTCOffsetMap.value(tz);
}

   int QmTime::getDSTUsage(const QDateTime& time, const QString& tz)

   int QmTime::getTimeDiff(const QDateTime& time, const QString& tz1, const QString& tz2)
*/
#endif

bool QmTime::setAutosync(bool enable)
{
    s_AutoSync = enable;
    return s_setAutoSync;
}

bool QmTime::setAutoSystemTime(QmTime::AutoSystemTimeStatus status)
{
    s_AutoSystemTime = status;
    return s_setAutoSystemTime;
}

bool QmTime::setAutoTimeZone(QmTime::AutoTimeZoneStatus status)
{
    s_AutoTimeZone = status;
    return s_setAutoTimeZone;
}


int QmTime::getAutosync(void)
{
    return s_AutoSystemTime == QmTime::AutoSystemTimeOn && 
	    s_AutoTimeZone == QmTime::AutoTimeZoneOn;
}

QmTime::AutoSystemTimeStatus
QmTime::autoSystemTime()
{
    return s_AutoSystemTime;
}

QmTime::AutoTimeZoneStatus
QmTime::autoTimeZone()
{
    return s_AutoTimeZone;
}
#ifndef HAVE_QMSYSTEM

QmDisplayState::QmDisplayState(QObject *parent):
    QObject(parent)
{

}

QmDisplayState::~QmDisplayState()
{

}

#endif

#endif
}
