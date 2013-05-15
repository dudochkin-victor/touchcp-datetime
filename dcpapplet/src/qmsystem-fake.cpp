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
#include "qmsystem-fake.h"
#include <QFile>
#include <QProcess>
#include <QDebug>
namespace MeeGo
{
const QString SetDate("sudo /usr/lib/duicontrolpanel/applets/setdate");
const QString tzinfo("/etc/localtime");
const QString zoneinfodir("/usr/share/zoneinfo/");
QmTime::QmTime(QObject *parent):
    QObject(parent)
{

}

QmTime::~QmTime()
{

}

int QmTime::getAutosync()
{
    return 0;
}

bool QmTime::setAutosync(bool)
{
    return false;
}

bool QmTime::setTime(const QDateTime& time)
{
    QString cmdLine;
    cmdLine = SetDate + " d " + time.toString("yyyy M d h m s");

    qDebug() << cmdLine; 
    int exitStatus = QProcess::execute(cmdLine);
   
    if (exitStatus)
        qWarning("Unable to set datetime %i",exitStatus);
    else
        emit timeOrSettingsChanged(MeeGo::QmTimeTimeChanged);
    return exitStatus == 0;
}

bool QmTime::getTimezone(QString& timezone)
{
    QFile file(tzinfo);
    timezone = file.symLinkTarget();
    timezone.replace(zoneinfodir, "");
    return true;
}

 bool QmTime::setTimezone(const QString timezone)
{
    QString cmdLine;
    cmdLine = SetDate + " tz " + timezone;

    qDebug() << cmdLine; 
    int exitStatus = QProcess::execute(cmdLine);
   
    if (exitStatus)
        qWarning("Unable to set datetime %i",exitStatus);
    else
        emit timeOrSettingsChanged(MeeGo::QmTimeTimeChanged);
    return exitStatus == 0;
    return false;
}

QmTime::AutoSystemTimeStatus 
QmTime::autoSystemTime() 
{return QmTime::AutoSystemTimeOff;}

QmTime::AutoTimeZoneStatus 
QmTime::autoTimeZone() 
{return QmTime::AutoTimeZoneOff;}

bool
QmTime::setAutoSystemTime(QmTime::AutoSystemTimeStatus) {return false;}
bool 
QmTime::setAutoTimeZone(QmTime::AutoTimeZoneStatus) {return false;}

QmDisplayState::QmDisplayState(QObject *parent):
    QObject(parent)
{

}

QmDisplayState::~QmDisplayState()
{

}

} // namespace Maemo
// vim: sw=4 sts=4 et tw=100
