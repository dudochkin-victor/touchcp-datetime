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
#include <QSignalSpy>
#include <brief.h>
#include <dcpwidgettypes.h>
#include "settings.h"
#include "translation.h"
#include "ut_brief.h"
void Ut_Brief::init()
{
    m_subject = new Brief(View::Date);
}

void Ut_Brief::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_Brief::initTestCase()
{
}

void Ut_Brief::cleanupTestCase()
{
}
void Ut_Brief::testConstruction()
{

    Settings& s = Settings::instance();

    QVERIFY(m_subject); // constructed with View::Date in Ut_Brief::init() by default
    QSignalSpy spy1(m_subject, SIGNAL(valuesChanged()));
    s.setDate(2010, 1, 1);
    QVERIFY(spy1.count() == 1);
    delete m_subject;
    
    m_subject = new Brief(View::Time);
    QVERIFY(m_subject); 
    QSignalSpy spy2(m_subject, SIGNAL(valuesChanged()));
    s.setTime(3, 20);
    QVERIFY(spy2.count() == 1);
    delete m_subject;
    
    m_subject = new Brief(View::TimeZone);
    QVERIFY(m_subject); 
//  QSignalSpy spy3(m_subject, SIGNAL(valuesChanged()));
//  s.setTimezone("Helsinki/Finland");
//  QVERIFY(spy3.count() == 1);
    delete m_subject;

    m_subject = new Brief(View::Main);
    QSignalSpy spy4(m_subject, SIGNAL(valuesChanged()));
    s.setTime(3, 20);
    QVERIFY(spy4.count() == 1);
    QVERIFY(m_subject); 
    
}

void Ut_Brief::testTitleText()
{
    m_subject->m_PartId = View::Date;
    QCOMPARE(m_subject->titleText(), QString(qtTrId(QtnCommSettingsDate)));
    
    m_subject->m_PartId = View::Time;
    QCOMPARE(m_subject->titleText(), QString(qtTrId(QtnCommSettingsTime)));
    
    m_subject->m_PartId = View::TimeZone;
    QCOMPARE(m_subject->titleText(), QString(qtTrId(QtnCommSettingsTimeZone)));
    
    m_subject->m_PartId = View::Main;
    QCOMPARE(m_subject->titleText(), QString(qtTrId(QtnDateTimeTitle)));
    

}

void Ut_Brief::testValueText()
{
    QVERIFY(!m_subject->valueText().isEmpty());
}

void Ut_Brief::testWidgetTypeID()
{
    QVERIFY(m_subject->widgetTypeID() == DcpWidgetType::Label);
}


QTEST_APPLESS_MAIN(Ut_Brief)
