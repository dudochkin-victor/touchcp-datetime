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

#ifdef HAVE_CELLULAR_QT
#include <systemcontrol.h>
#else
#include "cellular-fake.h"
#endif

#include "systemcontroldata.h"

bool s_Power = false;
Cellular::SystemControl::Status s_Status = Cellular::SystemControl::NoService;
bool s_IsValid = false;

void setSysControlStatus(Cellular::SystemControl::Status value)
{
    s_Status = value;
}

void setSysControlIsValid(bool value)
{
    s_IsValid = value;
}
namespace Cellular {



SystemControl::SystemControl(QObject *parent) :
#ifdef HAVE_CELLULAR_QT
    QObject(parent), d(0)
#else
        QObject(parent)
#endif
{
}

SystemControl::~SystemControl()
{
}

#ifdef HAVE_CELLULAR_QT
bool SystemControl::power() const
{
    Q_ASSERT(false); /*unused*/
    return s_Power;
}
#endif

SystemControl::Status SystemControl::status() const
{
    return s_Status;
}

#ifdef HAVE_CELLULAR_QT
SystemControl::Activity SystemControl::activity() const
{
    return UnknownActivity;
}

void SystemControl::setPower(bool value)
{
    Q_ASSERT(false); /*unused*/
    s_Power = value;
}
#endif

bool SystemControl::isValid() const
{
    return s_IsValid;
}


}

