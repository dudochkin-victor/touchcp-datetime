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

#ifdef HAVE_CELLULAR_QT
#include <systemcontrol.h>
#include <sim.h>
#else
#include "cellular-fake.h"
#endif

namespace Cellular {
namespace SIM {

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

}
}
