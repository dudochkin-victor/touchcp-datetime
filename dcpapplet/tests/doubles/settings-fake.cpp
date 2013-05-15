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
#include "settings.h"

class SettingsFake
{
public:
    int hour;
    int min;
    int year;
    int month;
    int day;
};

static SettingsFake data;

Settings::Settings(QObject* parent):
    QObject(parent)
{
    Q_UNUSED(parent);
}

Settings::~Settings()
{
}

void Settings::timeOrSettingsChangedSlot(QmTimeWhatChanged what)
{
    Q_UNUSED(what);
}

Settings& Settings::instance()
{
    static Settings _instance;
    return _instance;
}

bool Settings::cellularNetworkIsAvailable()
{
    return true;
}

bool Settings::isSimInserted()
{
    return true;
}

void Settings::onSimStatusChanged (SIMStatus::Status)
{
}

bool Settings::getAutoSync()
{
    return false;
}

bool Settings::setAutoSync(bool set)
{
    Q_UNUSED(set);
    return false;
}

void Settings::getTime(int &hour, int &min) const
{
    hour = data.hour;
    min = data.min;
}

bool Settings::setTime(int hour, int min)
{
    data.hour = hour;
    data.min = min;
    bool ret = true;
    emit timeChanged();
    return ret;
}

void Settings::getDate(int &year, int &month, int &day) const
{
    year = data.year;
    month = data.month;
    day = data.day;
}

bool Settings::setDate(int year, int month, int day)
{
    bool ret = true;
    data.year = year;
    data.month = month;
    data.day = day;
    emit dateChanged();
    return ret;
}

bool Settings::setDateTime(const QDateTime& newDate)
{
    Q_UNUSED(newDate);
    return true;
}

QString Settings::getTimezone()
{
    return "";
}

bool Settings::setTimezone(QString timezone)
{
    Q_UNUSED(timezone);
    return false;
}

TimeFormatId Settings::getTimeFormat()
{
    TimeFormatId tf = TimeFormat24h;
    return tf;
}

TimeFormatId Settings::getEffectiveTimeFormat()
{
    return TimeFormat24h;
}

void Settings::setTimeFormat(TimeFormatId id)
{
    Q_UNUSED(id);
}

ClockTypeId Settings::getClockType()
{
    return ClockTypeDigital;
}

void Settings::setClockType(ClockTypeId id)
{
    Q_UNUSED(id);
}

void Settings::timerTimeoutSlot()
{
}

void Settings::displayStateChangedSlot(
        MeeGo::QmDisplayState::DisplayState state)
{
    Q_UNUSED(state);
}

