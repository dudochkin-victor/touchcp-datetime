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

#include <string>

#include <unicode/timezone.h>

//#include <networkoperator.h>

#include <QObject>
#include <QVariant>
#include <QDebug>
#include <QStringList>
#include <MLocale>

#include "timezonemodel.h"
#ifdef HAVE_CITIES
#include <mlocationdatabase.h>
#else
#include "mlocationdatabase-fake.h"
#endif

static const int g_MinutesPerHour = 60;
static const int g_SecondsPerMinute = 60;
static const int g_MiliSecondsPerSeconds = 1000;

QMap<QString, QString> TimeZoneModel::sm_CityNames;
QMap<QString, QString> TimeZoneModel::sm_CityInCountryNames;

TimeZoneModel& TimeZoneModel::instance()
{
    qDebug() << Q_FUNC_INFO;                                                                                      
    static TimeZoneModel model;
    model.setObjectName("TimeZoneModel");
    return model;
}

QString TimeZoneModel::toGmt(QString timezone)
{
    if (m_LookupByTimeZone.contains(timezone)) {
        MCity city = m_LookupByTimeZone.value(timezone, MCity());
        return toGmt(city.timeZoneTotalOffset());
    }
    return toGmt(0);
}

QString TimeZoneModel::toGmt(qint32 offset)
{
    int mins = offset / (g_SecondsPerMinute * g_MiliSecondsPerSeconds);
    QString Gmt;

    Gmt.sprintf("GMT%+d:%02d",
            mins/g_MinutesPerHour,
            mins%g_MinutesPerHour);
    return Gmt;
}

TimeZoneModel::TimeZoneModel(QObject *parent) :
    MAbstractItemModel(parent)
{
    populateModel();
}

TimeZoneModel::~TimeZoneModel()
{
}

// return invalid index if timezone not found in model
QModelIndex TimeZoneModel::getIndex(const QString &timezone) const
{
    if (!m_TimeZoneIndexMap.contains(timezone)) {
        qWarning() << "timezone not in model:" << timezone;
        return QModelIndex();
    }

    QVector<int> indexVec = m_TimeZoneIndexMap[timezone];
    QModelIndex parent = index(indexVec[0], 0);
    QModelIndex idx = index(indexVec[1], 0, parent);
    return idx;
}

QString TimeZoneModel::equalityKey(const MCity& city) const
{
   return city.country().key() + city.timeZone();
}
QString TimeZoneModel::tmzCity(QString timezone) const
{
    if (m_LookupByTimeZone.contains(timezone))
    {
        MCity city = m_LookupByTimeZone.value(timezone, MCity());

        return  equalCityNames(equalityKey(city));
    }
    return QString();
}

// TODO: translation of the cities should be cached
static bool compareCityName(MCity city1, MCity city2)
{
    return TimeZoneModel::cityName(city1) < TimeZoneModel::cityName(city2);
}
QString TimeZoneModel::cityName(const MCity& city)
{
    return sm_CityNames.value(city.key(), "-");
}

void TimeZoneModel::populateModel()
{
#ifdef HAVE_CITIES
    m_LocationDb = new MLocationDatabase();
#else
    m_LocationDb = new MLocationDatabaseFake();
#endif
    m_Cities = m_LocationDb->cities();
    qSort(m_Cities.begin(), m_Cities.end(), compareCityName);
    QSet<QString> tmz;
    QList<MCity> cityItems;
    
    for(QList<MCity>::iterator iter = m_Cities.begin();
       iter != m_Cities.end(); iter++)
      {
        MCity city = *iter;
    	sm_CityNames[city.key()] = qtTrId(qPrintable(city.key())); 
        sm_CityInCountryNames[city.key()] = qtTrId(qPrintable(city.country().key())); 
        QString key = equalityKey(city);
        if (m_EqualCities.contains(key)) {
            m_EqualCities[key].append(city);
        }
        else //if (!tmz.contains(city.timeZone()))
        {
            tmz.insert(city.timeZone());
	        cityItems.append(city);
            m_LookupByTimeZone[city.timeZone()] = city;
            QChar label = groupLabel(city);
            int groupIndex = m_GroupLabels.indexOf(label);
            if (groupIndex == -1) {
                m_GroupLabels.append(label);
                groupIndex = m_GroupLabels.count() - 1;
            }
             m_GroupMap[groupIndex].append(city);
             QVector<int> indexVec(2);
             indexVec[0] = groupIndex;
             indexVec[1] = m_GroupMap[groupIndex].count() - 1;
             m_TimeZoneIndexMap[city.timeZone()] = indexVec;
             m_EqualCities[key].append(city);
      }
    } 
   for(QList<MCity>::iterator iter = m_Cities.begin();
       iter != m_Cities.end(); iter++)
        {
            MCity city = *iter;
	        cacheCity(city);
        }

}
QString TimeZoneModel::equalCityNames(const QString& key) const
{
    if (!m_EqualCities.contains(key))
	return "";

    QList<MCity> cities = m_EqualCities[key];
    qSort(cities.begin(), cities.end(), compareCityName);
    if (cities.count() > 1) {
	return cityName(cities[0]) + ", " + cityName(cities[1]);
    } else
	return cityName(cities[0]);
}
QChar TimeZoneModel::groupLabel(const MCity& city) const
{
    QString translatedStr = sm_CityInCountryNames.value(city.key(), "-");
    return translatedStr[0];
}
void TimeZoneModel::updateData(const QModelIndex &first, const QModelIndex &last)
{
    qDebug() << Q_FUNC_INFO;
//    if (first.isValid() && last.isValid() && first < last)
        emit dataChanged(first, last);
}

int TimeZoneModel::groupCount() const
{
    return m_GroupLabels.count();
}
int TimeZoneModel::rowCountInGroup(int group) const
{
    if (group == -1) {
        return m_Cities.count();
    }

    return m_GroupMap[group].count();
}

QString TimeZoneModel::groupTitle(int group) const
{
    if (group > -1 && group < m_GroupLabels.count())
        return m_GroupLabels[group];
    
    return QString();
}

QVariant TimeZoneModel::itemData(int row, int group, int role) const
{

//    qDebug() << Q_FUNC_INFO << row << group << role;                                      
    MCity city;                                                                           
    if (group >= 0 && row >= 0) {                                                         
        city = m_GroupMap[group].at(row);                                                    
    } else {                                                                              
        city = m_Cities.at(row);                                                             
    }                                                              
   QString key = city.key() + QString::number(role);
   return m_CityDataCache.value(key, QVariant());                   
}

void TimeZoneModel::cacheCity(MCity& city)
{
    QString cities = equalCityNames(equalityKey(city));
    QString countryName = qtTrId(qPrintable(city.country().key())); 
    QString offset = toGmt(city.timeZoneTotalOffset()) ;
  
  
    QString filterStr = countryName + " " + cities + " " 
			+ city.timeZone() + " " + offset;
    m_CityDataCache[city.key() + QString::number(FilterRole)] = QVariant(filterStr);
            
    QString sortStr = countryName + " " + cities + " " + offset ;
    m_CityDataCache[city.key() + QString::number(SortRole)] = QVariant(sortStr);
            
    QStringList list;
    list << countryName << cities << city.timeZone() << offset;

    m_CityDataCache[city.key() + QString::number(Qt::DisplayRole)] = QVariant(list);
}
