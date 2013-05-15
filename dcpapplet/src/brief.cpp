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
#include <QtDebug>

#include <MLocale>

#include "settings.h"
#include "timezonemodel.h"
#include "debug.h"
#include "brief.h"
#include "translation.h"
#include "dcpwidgettypes.h"

Brief::Brief(int partId)
    : m_PartId(partId)
{
    Settings &set = Settings::instance();
    if (    partId == View::Time ||
            partId == View::Main) {
        connect(&set, SIGNAL(timeChanged()),
                 this, SIGNAL(valuesChanged()));
    }
    if(partId == View::Date) {
        connect(&set, SIGNAL(dateChanged()),
                 this, SIGNAL(valuesChanged()));
    }
    if(partId == View::TimeZone){
        connect(&set, SIGNAL(datetimeSettingsChanged()),
                 this, SIGNAL(valuesChanged()));
    }
    connect(&set, SIGNAL(datetimeChanged()),
             this, SIGNAL(valuesChanged()));
    connect(&set, SIGNAL(localeChanged()),
             this, SIGNAL(valuesChanged()));
}

Brief::~Brief()
{
}

QString Brief::titleText() const
{
    QString result;
    QDateTime now = QDateTime::currentDateTime();

    switch (m_PartId) {
        case View::TimeZone :
            result = qtTrId(QtnCommSettingsTimeZone);
            break;
        case View::Date :
            result = qtTrId(QtnCommSettingsDate);
            break;
        case View::Time :
            result = qtTrId(QtnCommSettingsTime);
            break;
        case View::Main :
        default:
            result = qtTrId(QtnDateTimeTitle);
            break;
    }

    return result;
}

QString Brief::valueText() const
{
    MLocale locale;
    QString result;
    QDateTime now = QDateTime::currentDateTime();

    switch (m_PartId) {
        case View::TimeZone :
            result = Settings::instance().getTimezone();
            break;
        case View::Date :
            result = locale.formatDateTime(now, MLocale::DateFull,
                                           MLocale::TimeNone);
            break;
        case View::Time :
            result = locale.formatDateTime(now, MLocale::DateNone,
                                           MLocale::TimeShort);
            break;
        case View::Main :
        default:
            result = locale.formatDateTime(now, MLocale::DateNone,
                                           MLocale::TimeShort)
                + " " + locale.formatDateTime(now, MLocale::DateShort,
                                           MLocale::TimeNone); 
            break;
    }

    return result;
}

int Brief::widgetTypeID() const
{
    return DcpWidgetType::Label;
}
