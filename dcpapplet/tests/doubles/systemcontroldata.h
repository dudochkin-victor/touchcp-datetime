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
#ifndef SYSTEMCONTROLDATA_H
#define SYSTEMCONTROLDATA_H
#ifdef HAVE_CELLULAR_QT
#include <systemcontrol.h>
#else
#include "cellular-fake.h"
#endif


void setSysControlStatus(Cellular::SystemControl::Status value);
void setSysControlIsValid(bool value);

#endif // SYSTEMCONTROLDATA_H
