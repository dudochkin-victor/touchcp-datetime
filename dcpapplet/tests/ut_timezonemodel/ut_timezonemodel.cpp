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
#include <mcity.h>


#include "ut_timezonemodel.h"

void Ut_TimeZoneModel::init()
{
}

void Ut_TimeZoneModel::cleanup()
{
}

void Ut_TimeZoneModel::initTestCase()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_TimeZoneModel::cleanupTestCase()
{
}

void Ut_TimeZoneModel::testInstance()
{
    TimeZoneModel &model = TimeZoneModel::instance();
    model.setGrouped(true);
    QVERIFY(&model == &(TimeZoneModel::instance()));
}

void Ut_TimeZoneModel::testGroupCount()
{
    TimeZoneModel &model = TimeZoneModel::instance();
    model.setGrouped(true);
    QCOMPARE(model.groupCount(), model.m_GroupLabels.count());
}

void Ut_TimeZoneModel::testRowCountInGroup()
{
    TimeZoneModel &model = TimeZoneModel::instance();
    model.setGrouped(true);
    QCOMPARE(model.rowCountInGroup(-1), model.m_Cities.count());
    for (int i=0;i < model.m_GroupMap.keys().count(); i++)
        QCOMPARE(model.rowCountInGroup(i), model.m_GroupMap[i].count());
}

void Ut_TimeZoneModel::testGroupTitle()
{

    TimeZoneModel &model = TimeZoneModel::instance();
    model.setGrouped(true);
    for (int i=0;i < model.m_GroupLabels.count(); i++)
        QCOMPARE(model.groupTitle(i), QString(model.m_GroupLabels[i]));
    int badIdx = model.m_GroupLabels.count();
    QCOMPARE(model.groupTitle(badIdx), QString());
    badIdx = -1;
    QCOMPARE(model.groupTitle(badIdx), QString());
}

void Ut_TimeZoneModel::testUpdateData()
{
    TimeZoneModel &model = TimeZoneModel::instance();
    model.setGrouped(true);
    QSignalSpy spy(&model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)));
    model.updateData(QModelIndex(), QModelIndex());
    QCOMPARE(spy.count(), 1);
    model.updateData(QModelIndex(), QModelIndex());
    QCOMPARE(spy.count(), 2);
}

void Ut_TimeZoneModel::testItemData()
{
    TimeZoneModel &model = TimeZoneModel::instance();
    model.setGrouped(true);
    int row = 1;
    int group = 0;
    QVariant data1 = model.itemData(row, group, Qt::DisplayRole);
    MCity city = model.m_GroupMap[group].at(row);
    
    QStringList list = data1.toStringList();
    QCOMPARE(list[0], city.country().key());
    QCOMPARE(list[1], city.key());
    QCOMPARE(list[2], city.timeZone());
    QCOMPARE(list[3], TimeZoneModel::instance().toGmt(city.timeZone()));
    QVariant data2 = model.itemData(row, group, TimeZoneModel::FilterRole);
    QString str = data2.toString();
    QString formatStr = qtTrId(qPrintable(city.country().key()))
            + " " + qtTrId(qPrintable(city.key())) + " " + city.timeZone() 
	    + " " + TimeZoneModel::instance().toGmt(city.timeZone()) ;
    QCOMPARE(str, formatStr);
    QVariant data3 = model.itemData(row, group, TimeZoneModel::SortRole);
    QString str2 = data3.toString();
    QString formatStr2 = qtTrId(qPrintable(city.country().key()))
            + " " + qtTrId(qPrintable(city.key())) + 
	    + " " + TimeZoneModel::instance().toGmt(city.timeZone()) ;
    QCOMPARE(str2, formatStr2);
}

void Ut_TimeZoneModel::testGetIndex()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_TimeZoneModel::testToGmt()
{
    QCOMPARE(TimeZoneModel::instance().toGmt(""), QString("GMT+0:00"));

}

void Ut_TimeZoneModel::testPopulateModel()
{
}


void Ut_TimeZoneModel::testGroupLabel()
{
    TimeZoneModel &model = TimeZoneModel::instance();
    model.setGrouped(true);
    const MCity &city = model.m_Cities.at(0);
    QVERIFY(!QString(model.groupLabel(city)).isEmpty());
}


QTEST_APPLESS_MAIN(Ut_TimeZoneModel)
