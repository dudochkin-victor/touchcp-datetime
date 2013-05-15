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

#include "cellular-fake.h"

namespace Cellular
{

SystemControl::SystemControl(QObject *parent):
    QObject(parent)
{

}

SystemControl::~SystemControl()
{

}

SystemControl::Status SystemControl::status() const
{
    return UnknownStatus;
}

bool SystemControl::isValid() const
{
    return false;
}

namespace SIM
{

SIMStatus::SIMStatus(QObject *parent):
    QObject(parent)
{

}

SIMStatus::~SIMStatus()
{

}

void SIMStatus::status()
{
    emit statusChanged(Ok);
}
} // namespace SIM

} // namespace Cellular
// vim: sw=4 sts=4 et tw=100
