#include "mlocationdatabase-fake.h"
#include <unicode/timezone.h>
#include <QDebug>
#include <QFile>
#include <QRegExp>
#include <QStringList>

static const QString countryListFile = "/usr/share/duicontrolpanel-datetimeapplet/iso3166.tab";

MLocationDatabaseFake::MLocationDatabaseFake()
{
    createCities();
}
MLocationDatabaseFake::~MLocationDatabaseFake()
{
}

QList<MCountry> MLocationDatabaseFake::countries()
{
    return QList<MCountry>();
}

QList<MCity> MLocationDatabaseFake::cities()
{
    return m_Cities;
}

QList<MCity> MLocationDatabaseFake::citiesInCountry( const QString& countryKey )
{
    Q_UNUSED(countryKey);
    return QList<MCity>();
}



QList<MCity> MLocationDatabaseFake::matchingCities( const QString& searchString )
{
    Q_UNUSED(searchString);
    return QList<MCity>();
}

MCity MLocationDatabaseFake::nearestCity( qreal latitude, qreal longitude )
{
    Q_UNUSED(latitude);
    Q_UNUSED(longitude);
    return MCity();
}

void MLocationDatabaseFake::createCities()
{
    QMap<QString, QString>* countries = countriesMap();
    QMap<QString, QString>::const_iterator iter;

    for(iter = countries->begin(); iter != countries->end(); iter++)
    {
        UErrorCode status = U_ZERO_ERROR;                                       
        icu::StringEnumeration* tzids = icu::TimeZone::createEnumeration(
                                           iter.key().toAscii().data());
        const UnicodeString *next;

        for(next = tzids->snext(status);next;next = tzids->snext(status))
            {
                QString timezone(reinterpret_cast<const QChar*>(                    
                         next->getBuffer()), next->length());
                qDebug() << timezone;
                /* skip timezone names like: GB-Eire                                
                 * and hold only ones like: Area/City */                            
                if(!timezone.contains("/"))                                         
                    continue;   
                QString countryName = iter.value();
                countryName.replace("\n", "");
                addCity(timezone, countryName);
            }
        }
}

void MLocationDatabaseFake::addCity(const QString& timezone,
                                       const QString& countryName)
{
    MCity city;
    MCountry country;
    QString gmt;
    QString filter;
    QStringList item = timezone.split("/");
    QString cityName = item.at(item.size()-1);
    cityName.replace('_', ' ');

    /*** set GMT offset */
    icu::UnicodeString uZone = UnicodeString::fromUTF8(
            timezone.toUtf8().constData());

    int offset = icu::TimeZone::createTimeZone(uZone)->getRawOffset() / (60 * 1000);
    gmt.sprintf("GMT%+d:%02d", offset/60, offset%60);
    filter = countryName;
    filter += " ";
    filter += gmt;
    filter += " ";
    filter += cityName;

    if (m_CityFilter.contains(filter))
        return;
    m_CityFilter.insert(filter);
    city.setKey(cityName);
    city.setEnglishName(cityName);
    city.setLocalName(cityName);

    country.setKey(countryName);
    city.setCountry(country);
    city.setTimeZone(timezone);
    
    m_Cities.append(city);
}

QMap<QString, QString>* MLocationDatabaseFake::countriesMap()
{
    QMap<QString, QString> *map = new QMap<QString, QString>();
    QFile *file;

    file = new QFile(countryListFile);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)){
        qCritical("Could not read file %s", qPrintable(countryListFile));
        return map;
    }

    int lineNum = -1;
    while (!file->atEnd()) {
        QString country;
        QString line = file->readLine();
        lineNum++;

        if (line.startsWith("#"))
            continue;

        QStringList item = line.split(QRegExp("\\t"), QString::SkipEmptyParts);

        /* skip bad results/table lines those would break the follower code */
        if(item.size() < 2){
            qWarning("Less than two column found in file %s at line %d",
                    qPrintable(countryListFile),
                    lineNum);
            continue;
        }

        if(2 < item.size())
            qWarning("More than two column found in file %s at line %d",
                    qPrintable(countryListFile),
                    lineNum);

        country = item.at(1);

        /* country code => country name */
        /* key expected but value will not be unique */
        map->insert(item.at(0), country);
    }
    file->close();
    delete file;

    return map;
}
