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

#ifndef UT_SETTINGS_H
#define UT_SETTINGS_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/Settings class declaration
#include <settings.h>

Q_DECLARE_METATYPE(Settings*);

class Ut_Settings : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testInstance();
    void testCellularNetworkIsAvailable();
    void testAutoSync();
    void testTime();
    void testDate();
    void testDateTime();
    void testTimezone();
    void testTimeFormat();
    void testTimeOrSettingsChangedSlot();
    void testTimerTimeoutSlot();
    void testDisplayStateChangedSlot();
    

private:
    Settings* m_subject;
};
#endif
