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

#include <QtGui>
#include <QDebug>

#include <MTheme>
#include <MAction>
#include <MLibrary>

#include <DcpWidget>

#include "brief.h"
#include "translation.h"
#include "mainview.h"
#include "timezoneview.h"
#include "dateview.h"

#include "timeview.h"

#include "debug.h"

#include "applet.h"

#define VIEW_ID_NONE ""
#define VIEW_ID_MAIN "Main"
#define VIEW_ID_DATE "Date"
#define VIEW_ID_TIME "Time"
#define VIEW_ID_TIMEZONE "TimeZone"
#include <QTime>


#ifndef UNIT_TEST
M_LIBRARY
#endif
Q_EXPORT_PLUGIN2(datetimeapplet, Applet)

void Applet::init()
{
    m_RefererPage = View::None;
    m_LastConstructedView = View::None;
    QTimer::singleShot(0, this, SLOT(finishCreation()));
};

/* FIXME this is a hack because dcp not supports multiple pages properly. */
/*
 * When a subview is opened from dcp it should return to dcp so needs
 * referer View::None (-1). When a subview is opened from the main
 * view it should return to the main view so needs referer View::Main (>0).
 * It is the caller MainView that able to preset this value correctly.
 */
void Applet::refererToChangeWidgetSlot(View::Id ref)
{
    m_RefererPage = ref;
}
void Applet::finishCreation()
{
//      MTheme::loadCSS(QString(CSSDIR) + "datetimeapplet.css");
      MLocale locale;
      locale.installTrCatalog("date-time");
      locale.installTrCatalog("countries");
      MLocale::setDefault(locale);

}
DcpStylableWidget* Applet::constructStylableWidget(int viewId)
{

    DcpStylableWidget* ret;
    QTime t;
    t.start();
    switch (viewId) {
        case View::TimeZone :
            ret = new TimeZoneView();
            m_LastConstructedView = View::TimeZone;
            break;
        case View::Date :
            ret = new DateView();
            m_LastConstructedView = View::Date;
            break;
        case View::Time :
            ret = new TimeView();
            m_LastConstructedView = View::Time;
            break;
        case View::Main :
        default:
            ret = new MainView();
            connect(ret, SIGNAL(refererToChangeWidget(View::Id)),
                    this, SLOT(refererToChangeWidgetSlot(View::Id)));
            m_LastConstructedView = View::Main;
            break;
    }
    qDebug("Time elapsed: %d ms", t.elapsed());
    return ret;
}

QString Applet::title() const
{
    const char* msgid;
    switch(m_LastConstructedView){
        case View::TimeZone :
            msgid = QtnCommSettingsTimeZone;
            break;
        case View::Date :
            msgid = QtnCommTimeDatepickerTitle;
            break;
        case View::Time :
            msgid = QtnCommTimeTimepickerTitle;
            break;
        case View::Main :
        default:
            msgid = QtnCommSettingsDate;
            break;
    }
    return QString(qtTrId(msgid));
}

QVector<MAction*> Applet::viewMenuItems()
{
    QVector<MAction*> vector;
    return vector;
}

DcpBrief* Applet::constructBrief(int partId)
{
    return new Brief(partId);
}

int Applet::partID(const QString& part)
{

    static QMap<QString, int> parts;
    if (parts.isEmpty()){
        parts.insert(VIEW_ID_MAIN, View::Main);
        parts.insert(VIEW_ID_DATE, View::Date);
        parts.insert(VIEW_ID_TIME, View::Time);
        parts.insert(VIEW_ID_TIMEZONE, View::TimeZone);
    }

    int ret = parts[part];

    if(!ret){
        qCritical("Requested part name '%s' is unknown "
                "and no partId belongs to it. Defaulting to main view.",
                qPrintable(part));
        ret = View::Main;
    }

    return ret;
}


