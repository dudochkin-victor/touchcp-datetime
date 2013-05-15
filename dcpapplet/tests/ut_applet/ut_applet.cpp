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

#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include <applet.h>


#include "ut_applet.h"
#include "translation.h"
#include <MApplication>

void Ut_Applet::init()
{
    m_subject = new Applet();
}

void Ut_Applet::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_Applet::initTestCase()
{
 /*   int argc = 1;
    char *argv = (char*) "./ut_applet";
    MApplication *app = new MApplication(argc, &argv);
    Q_UNUSED(app);*/
}


void Ut_Applet::cleanupTestCase()
{
}

void Ut_Applet::testInit()
{
    QVERIFY(m_subject);
    m_subject->init();
    QCOMPARE(m_subject->m_RefererPage, View::None);
    QCOMPARE(m_subject->m_LastConstructedView, View::None);
}

void Ut_Applet::testConstructWidget()
{
    QVERIFY(m_subject->constructStylableWidget(View::Date));
    QCOMPARE(m_subject->m_LastConstructedView, View::Date);

    QVERIFY(m_subject->constructStylableWidget(View::Time));
    QCOMPARE(m_subject->m_LastConstructedView, View::Time);

    QVERIFY(m_subject->constructStylableWidget(View::TimeZone));
    QCOMPARE(m_subject->m_LastConstructedView, View::TimeZone);

    QVERIFY(m_subject->constructStylableWidget(View::Main));
    QCOMPARE(m_subject->m_LastConstructedView, View::Main);

}

void Ut_Applet::testConstructBrief()
{
    QVERIFY(m_subject->constructBrief(View::Date));
}

void Ut_Applet::testTitle()
{
    m_subject->m_LastConstructedView = View::TimeZone;
    QCOMPARE(m_subject->title(), qtTrId(QtnCommSettingsTimeZone));

    m_subject->m_LastConstructedView = View::Date;
    QCOMPARE(m_subject->title(), qtTrId(QtnCommTimeDatepickerTitle));

    m_subject->m_LastConstructedView = View::Time;
    QCOMPARE(m_subject->title(), qtTrId(QtnCommTimeTimepickerTitle));

    m_subject->m_LastConstructedView = View::Main;
    QCOMPARE(m_subject->title(), qtTrId(QtnCommSettingsDate));

}

void Ut_Applet::testViewMenuItems()
{
    QVERIFY(m_subject->viewMenuItems().isEmpty());
}

void Ut_Applet::testPartID()
{
    QVERIFY(m_subject->partID(QString("Time")) == View::Time); 
    QVERIFY(m_subject->partID(QString("TimeZone")) == View::TimeZone); 
    QVERIFY(m_subject->partID(QString("Date")) == View::Date); 
    QVERIFY(m_subject->partID(QString("Main")) == View::Main); 
}

void Ut_Applet::testRefererToChangeWidgetSlot() 
{
    m_subject->init();
    QCOMPARE(m_subject->m_RefererPage, View::None);
    m_subject->refererToChangeWidgetSlot(View::Time);
    QCOMPARE(m_subject->m_RefererPage, View::Time);
}


QTEST_APPLESS_MAIN(Ut_Applet)
