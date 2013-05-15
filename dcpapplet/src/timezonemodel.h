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

#ifndef TIMEZONEMODEL_H
#define TIMEZONEMODEL_H

#include <MAbstractItemModel>
#include <mcity.h>
class QModelIndex;
#ifdef HAVE_CITIES
class MLocationDatabase; 
#else
class MLocationDatabaseFake; 
#endif

class TimeZoneModel : public MAbstractItemModel {
    Q_OBJECT

    public:
        static TimeZoneModel& instance();
        ~TimeZoneModel();
        int groupCount() const;
        int rowCountInGroup(int group) const;
        QString groupTitle(int group) const;
        void updateData(const QModelIndex &first, const QModelIndex &last);
        QVariant itemData(int row, int group, int role) const;
        enum Columns {
            Country = 0,
            City,
            Timezone,
            Gmt,
            NumberOfColumns
        };

        enum ItemDataRole {
            SortRole = Qt::UserRole+1,
            FilterRole,
	    RoleCount,
        };


        QModelIndex getIndex(const QString &timezone) const;
        static QString toGmt(qint32 offset);
        QString toGmt(QString timezone);
        QString tmzCity(QString timezone) const;
        void populateModel();
	static QString cityName(const MCity& city);
        QString equalCityNames(const QString& key) const;
    private:
        QChar groupLabel(const MCity& city) const;
	QString equalityKey(const MCity& city) const;
        TimeZoneModel(QObject *parent=0);
	void cacheCity(MCity& city);
        QMultiMap<QString, int> m_LookupByCountryCode;
        QMap<QString, MCity> m_LookupByTimeZone;

#ifdef HAVE_CITIES
        MLocationDatabase *m_LocationDb; 
#else
        MLocationDatabaseFake *m_LocationDb; 

#endif
        QList<MCity> m_Cities;
        static QMap<QString, QString> sm_CityNames;
        static QMap<QString, QString> sm_CityInCountryNames;
        // timezone id -> (group, row) index vector
        QMap< QString,QVector<int> > m_TimeZoneIndexMap;
        QList<QChar> m_GroupLabels;                                                
        QMap<int, QList<MCity> > m_GroupMap;   
        QMap<QString, QVariant> m_CityDataCache;   
        QMap<QString, QList<MCity> > m_EqualCities;   
        friend class Ut_TimeZoneModel;
};

#endif

