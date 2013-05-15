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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QTime>
#include <QTimer>
#include <MGConfItem>

#ifdef HAVE_CELLULAR_QT
#include <systemcontrol.h>
#include <networktime.h>
#include <sim.h>
#else
#include "cellular-fake.h"
#endif

#ifdef HAVE_QMSYSTEM
#include <qmtime.h>
#include <qmdisplaystate.h>
#else
#include "qmsystem-fake.h"
#endif

class QDateTime;

using namespace MeeGo;
using namespace Cellular::SIM;

enum TimeFormatId {
    TimeFormatLocaleDefault,
    TimeFormat12h,
    TimeFormat24h
};

enum ClockTypeId {
    ClockTypeAnalog,
    ClockTypeDigital
};
class Settings: public QObject {
    public:
        Q_OBJECT;
        Q_ENUMS(TimeFormatId);
        Q_ENUMS(ClockTypeId);

    public:
        static Settings& instance();

        bool cellularNetworkIsAvailable();
        bool autoSystemTime();
        bool autoTimeZone();
        bool getAutoSync();
        bool setAutoSystemTime(bool set);
        bool setAutoTimeZone(bool set);
        bool setAutoSync(bool set);
        bool isSimInserted();

        void getTime(int &hour, int &min) const;
        bool setTime(int hour, int min);

        void getDate(int &year, int &month, int &day) const;
        bool setDate(int year, int month, int day);

        bool setDateTime(const QDateTime& newDate);

        QString getTimezone();
        bool setTimezone(QString timezone);
        TimeFormatId getTimeFormat();
        ClockTypeId getClockType();
        TimeFormatId getEffectiveTimeFormat();
        void setTimeFormat(TimeFormatId id);
        void setClockType(ClockTypeId id);

signals:
        void datetimeSettingsChanged();
        void datetimeChanged();
        void timeChanged();
        void dateChanged();
        void networkAvailabilityChanged(bool available);
        void localeChanged();

    private:
        Settings(QObject* parent = 0);
        ~Settings();
        QString guessCountryCodeByNetworkMcc();

        private slots:
            void timeOrSettingsChangedSlot(MeeGo::QmTimeWhatChanged);
        void timerTimeoutSlot();
        void displayStateChangedSlot(MeeGo::QmDisplayState::DisplayState);
        void onSimStatusChanged (SIMStatus::Status status);

    private:
        Cellular::SIM::SIMStatus m_simStatus;
        SIMStatus::Status m_currentSimStatus;
        Cellular::SystemControl m_CellSysCtl;
        MeeGo::QmTime m_Time;
        QTimer m_Timer;
        QTime m_OldTime;
        QDate m_OldDate;
        QmDisplayState m_DisplayState;
        QString m_TmzString;
        MGConfItem *m_TimeFormatGConfItem;
        MGConfItem *m_ClockTypeGConfItem;
        class MLocale *m_Locale;
#ifdef SBOX
        // use fake timezone setting in sbox
        QString m_Timezone;
        bool m_IsAutoSystemTime;
        bool m_IsAutoTimeZone;
#endif

        friend class Ut_Settings;
};

#endif
