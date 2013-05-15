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

#include <MLocale>

MLocale::MLocale(QObject *parent) : QObject(parent), d_ptr(0) {}

void MLocale::connectSettings() {}

QString MLocale::formatDateTime(const QDateTime &dateTime, 
                                DateType dateType, TimeType timeType, 
                                CalendarType calendarType) const {
    Q_UNUSED(dateTime);
    Q_UNUSED(dateType);
    Q_UNUSED(timeType);
    Q_UNUSED(calendarType);
    return QString("2111-11-11 11:11:11");
}

QString MLocale::formatNumber(int i) const {
    Q_UNUSED(i);
    return QString("11");
}

MLocale::TimeFormat24h MLocale::defaultTimeFormat24h() const {
    return MLocale::TwentyFourHourTimeFormat24h;
}

