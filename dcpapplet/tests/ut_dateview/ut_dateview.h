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

#ifndef UT_DATEVIEW_H
#define UT_DATEVIEW_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DateView class declaration
#include <dateview.h>

Q_DECLARE_METATYPE(DateView*);

class Ut_DateView : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testConstruction();
    void testBack();
    void testInitWidget();
    void testTitle();
    void testRetranslateUi();
    void testEnterDisplayEvent();
    void testDaySelected();
    void testTimeOrDateChangedSlot();
    void testDigitalDateChangedSlot();
    

private:
    DateView* m_subject;
};
#endif
