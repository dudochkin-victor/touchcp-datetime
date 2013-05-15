/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (directui@nokia.com)
**
** This file is part of libmeegotouch.
**
** If you have questions regarding the use of this file, please contact
** Nokia at directui@nokia.com.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#ifndef MLOCATIONDATABASE_FAKE_H
#define MLOCATIONDATABASE_FAKE_H

#include <QList>
#include <QMap>
#include <QSet>

#include <mcity.h>
#include <mcountry.h>


class MLocationDatabaseFake
{
  public:
    MLocationDatabaseFake();
    virtual ~MLocationDatabaseFake();

    /**
     * \brief returns a list with all known countries
     */
    QList<MCountry> countries();

    /**
     * \brief returns a list with all known cities
     */
    QList<MCity> cities();

    /**
     * \brief returns a list with all cities in a country
     */
    QList<MCity> citiesInCountry( const QString& countryKey );

    /**
     * \brief returns a list with all cities that contain the given searchString
     */
    QList<MCity> matchingCities( const QString& searchString );

    /**
     * \brief returns the city with the nearest position to the given location.
     */
    MCity nearestCity( qreal latitude, qreal longitude );
    static QMap<QString, QString>* countriesMap();
  private:
    void createCities();
    void addCity(const QString& timezone, const QString& country);
    QList<MCity> m_Cities;    
    QSet<QString> m_CityFilter;
};
#endif
