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
#include <MApplication>
#include <MLabel>
#include <MButton>
#include <autosyncbutton.h>
#include <translation.h>


#include "ut_autosyncbutton.h"

void Ut_AutoSyncButton::init()
{
    m_subject = new AutoSyncButton();
}

void Ut_AutoSyncButton::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_AutoSyncButton::initTestCase()
{
// int argc = 1;
// char *argv = (char*) "./ut_autosyncbutton";
// MApplication *app = new MApplication(argc, &argv);
// Q_UNUSED(app);
   QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_AutoSyncButton::cleanupTestCase()
{
}

void Ut_AutoSyncButton::testConstructionAndInitWidget()
{
    QVERIFY(m_subject);
//    QCOMPARE(m_subject->objectName(), QString("AutoSyncButton"));
    QCOMPARE(m_subject->m_BlockSettingAutoSync, 0);
    QVERIFY(m_subject->m_AutomaticLabel);
//    QCOMPARE(m_subject->m_AutomaticLabel->objectName(), QString("AutoSyncLabel"));
    QVERIFY(m_subject->m_SwitchButton);
//    QCOMPARE(m_subject->m_SwitchButton->objectName(), QString("AutoSyncToggleButton"));
    QCOMPARE(m_subject->m_SwitchButton->isCheckable(), true);
    QCOMPARE(m_subject->m_SwitchButton->viewType(), MButton::switchType);
    
}


void Ut_AutoSyncButton::testRetranslateUi()
{
    m_subject->retranslateUi();
    QCOMPARE(m_subject->m_AutomaticLabel->text(), qtTrId(QtnDateAutomaticUpdate));
}

void Ut_AutoSyncButton::testToggledSlot()
{
    m_subject->toggledSlot(true);
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_AutoSyncButton::testDatetimeSettingsChangedSlot()
{
    m_subject->datetimeSettingsChangedSlot();
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}


QTEST_APPLESS_MAIN(Ut_AutoSyncButton)
