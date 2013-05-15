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
#ifndef QMSYSTEMFAKE_H
#define QMSYSTEMFAKE_H
#include <QtCore/qobject.h>
#include <QTime>
#include <QDate>
#include <QDateTime>
#include <time.h>

namespace MeeGo {

enum QmTimeWhatChanged
{
    QmTimeTimeChanged = 0,
    QmTimeOnlySettingsChanged
};

class QmTime : public QObject, public QDateTime
{
    Q_OBJECT;
    public:
    QmTime(QObject *parent = 0);
    ~QmTime();
    enum AutoTimeZoneStatus { AutoTimeZoneOn = 1, AutoTimeZoneOff = 0, AutoTimeZoneUnknown = -1 } ;
    enum AutoSystemTimeStatus { AutoSystemTimeOn = 1, AutoSystemTimeOff = 0, AutoSystemTimeUnknown = -1 } ;
    int getAutosync();
    QmTime::AutoSystemTimeStatus autoSystemTime();
    QmTime::AutoTimeZoneStatus autoTimeZone();
    bool setAutoSystemTime(QmTime::AutoSystemTimeStatus);
    bool setAutoTimeZone(QmTime::AutoTimeZoneStatus);
    bool setAutosync(bool enable);
    bool setTime(const QDateTime& time);
    bool getTimezone(QString& s);
    bool setTimezone(const QString tz);
Q_SIGNALS:
    void timeOrSettingsChanged(MeeGo::QmTimeWhatChanged what);
};

class QmDisplayState : public QObject
{
    Q_OBJECT
    Q_ENUMS(DisplayState)
    public:
    QmDisplayState(QObject *parent = 0);
    ~QmDisplayState();
    enum DisplayState
    {
        Off = -1,
        Dimmed = 0,
        On = 1,
        Unknown
    };


Q_SIGNALS:
    void displayStateChanged(MeeGo::QmDisplayState::DisplayState state);
};

}

#endif
