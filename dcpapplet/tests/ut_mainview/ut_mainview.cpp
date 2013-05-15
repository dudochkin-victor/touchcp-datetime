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

#include <mainview.h>

#include "drilllistitem.h" 
#include <MComboBox>
#include <MStylableWidget>
#include "qgraphicswidget-fake.h"
#include "ut_mainview.h"
#include <QSignalSpy>

MStylableWidget::MStylableWidget (QGraphicsItem *)
{
}

void Ut_MainView::init()
{
    m_subject = new MainView();
    m_subject->finishMainView();
}

void Ut_MainView::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_MainView::initTestCase()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_MainView::cleanupTestCase()
{
}
void Ut_MainView::testConstruction()
{
    QVERIFY(m_subject);
}

void Ut_MainView::testBack()
{
    QSignalSpy spy(m_subject, SIGNAL(refererToChangeWidget(View::Id))); 
    QVERIFY(m_subject->back());
    QCOMPARE(spy.count(), 1);
}

void Ut_MainView::testInitWidget()
{
    // initWidget() was called by constructor, but tested here

   // QCOMPARE(m_subject->objectName(), QString("DcpDateTimeAppletMainView"));
    QVERIFY(m_subject->m_Locale);
    QVERIFY(m_subject->m_TimeButton);
    QVERIFY(m_subject->m_TimeFormatCBox);
    QVERIFY(m_subject->m_DateButton);
    QVERIFY(m_subject->m_TimeZoneButton);
}

void Ut_MainView::testTitle()
{
    QCOMPARE(m_subject->title(), QString("qtn_date_time_title"));
}

void Ut_MainView::testRetranslateUi()
{
    m_subject->m_DateButton->setTitle("");
    m_subject->m_TimeButton->setTitle("");
    m_subject->m_TimeZoneButton->setTitle("");
    m_subject->m_TimeFormatCBox->setTitle("");
    m_subject->m_DateButton->setSubtitle("");
    m_subject->m_TimeButton->setSubtitle("");
    m_subject->m_TimeZoneButton->setSubtitle("");
    m_subject->m_TimeFormatCBox->setTitle("");
    m_subject->m_TimeFormatCBox->setItemText(MainView::TimeFormatCBoxIndex12h,
                                             "");
    m_subject->m_TimeFormatCBox->setItemText(MainView::TimeFormatCBoxIndex24h,
                                             "");
    m_subject->retranslateUi();
    QVERIFY(!m_subject->m_DateButton->title().isEmpty());
    QVERIFY(!m_subject->m_TimeButton->title().isEmpty());
    QVERIFY(!m_subject->m_TimeZoneButton->title().isEmpty());
    QVERIFY(!m_subject->m_DateButton->subtitle().isEmpty());
    QVERIFY(!m_subject->m_TimeButton->subtitle().isEmpty());
    QVERIFY(!m_subject->m_TimeZoneButton->subtitle().isEmpty());
    QVERIFY(!m_subject->m_TimeFormatCBox->title().isEmpty());
    QVERIFY(!m_subject->m_TimeFormatCBox->itemText(MainView::TimeFormatCBoxIndex12h).isEmpty());
    QVERIFY(!m_subject->m_TimeFormatCBox->itemText(MainView::TimeFormatCBoxIndex24h).isEmpty());
}

void Ut_MainView::testShowTimeZoneView()
{
    QSignalSpy spy1(m_subject,SIGNAL(changeWidget(int)));
    m_subject->showTimeZoneView();
    QCOMPARE(spy1.count(), 1);
    QCOMPARE(spy1.takeFirst().at(0).toInt(), int(View::TimeZone));
}

void Ut_MainView::testUpdateTimeText()
{
    m_subject->m_TimeButton->setTitle("");
    m_subject->m_TimeButton->setSubtitle("");
    m_subject->updateTimeText(); 
    QCOMPARE(m_subject->m_TimeButton->title(),
                QString("qtn_comm_settings_time"));
    QVERIFY(!m_subject->m_TimeButton->subtitle().isEmpty());
/*    QTime time;
    qDebug() << m_subject->m_TimeButton->subtitle();
    time.fromString(m_subject->m_TimeButton->subtitle(),
                    "hh:mm:ss");
    QVERIFY(time.isValid());
*/
}

void Ut_MainView::testUpdateDateText()
{
    m_subject->m_DateButton->setTitle("");
    m_subject->m_DateButton->setSubtitle("");
    m_subject->updateDateText(); 
    QCOMPARE(m_subject->m_DateButton->title(),
                QString("qtn_comm_settings_date"));
    QVERIFY(!m_subject->m_DateButton->subtitle().isEmpty());
}

void Ut_MainView::testUpdateTimeZoneText()
{
    m_subject->m_TimeZoneButton->setTitle("");
    m_subject->m_TimeZoneButton->setSubtitle("");
    m_subject->updateTimeZoneText(); 
    QCOMPARE(m_subject->m_TimeZoneButton->title(),
                QString("qtn_comm_settings_timezone"));
    QVERIFY(!m_subject->m_TimeZoneButton->subtitle().isEmpty());
}

void Ut_MainView::testUpdateTimeFormatText()
{
    m_subject->m_TimeFormatCBox->setTitle("");
    m_subject->m_TimeFormatCBox->setItemText(MainView::TimeFormatCBoxIndex12h,
                                             "");
    m_subject->m_TimeFormatCBox->setItemText(MainView::TimeFormatCBoxIndex24h,
                                             "");
    m_subject->updateTimeFormatText();
    QCOMPARE(m_subject->m_TimeFormatCBox->title(),
         QString("qtn_date_time_format"));
    QCOMPARE(m_subject->m_TimeFormatCBox->itemText(MainView::TimeFormatCBoxIndex12h),
             QString("qtn_comm_time_format_12"));

    QCOMPARE(m_subject->m_TimeFormatCBox->itemText(MainView::TimeFormatCBoxIndex24h),
             QString("qtn_comm_time_format_24"));
}

void Ut_MainView::testShowDateView()
{
    QSignalSpy spy1(m_subject,SIGNAL(changeWidget(int)));
    m_subject->showDateView();
    QCOMPARE(spy1.count(), 1);
    QCOMPARE(spy1.takeFirst().at(0).toInt(), int(View::Date));
}

void Ut_MainView::testShowTimeView()
{
    QSignalSpy spy1(m_subject,SIGNAL(changeWidget(int)));
    m_subject->showTimeView();
    QCOMPARE(spy1.count(), 1);
    QCOMPARE(spy1.takeFirst().at(0).toInt(), int(View::Time));
}

void Ut_MainView::testDatetimeChangedSlot()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_MainView::testDatetimeSettingsChangedSlot()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_MainView::testTimeformatCBoxActivatedSlot()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}



QTEST_APPLESS_MAIN(Ut_MainView)
