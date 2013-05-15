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

#ifndef CELLULARQT_FAKE_H
#define CELLULARQT_FAKE_H

#include <QtCore/QObject>


namespace Cellular
{
class SystemControl : public QObject
{

    Q_OBJECT

public:
    SystemControl(QObject *parent=0);
    ~SystemControl();

    enum Status {
        UnknownStatus = -1,
        FullService,
        LimitedService,
        NoService,
        ModemFailure,
    };

    Status status() const;
    bool isValid() const;
};

namespace SIM
{

enum SIMError
{
    NoError = 0
};

class SIMStatus: public QObject
{
    Q_OBJECT

public:
    enum Status
    {
        UnknownStatus = -1,
        Ok,
        NoSIM
    };

    SIMStatus(QObject *parent=0);
    ~SIMStatus();

public Q_SLOTS:
    void status();

Q_SIGNALS:
    void statusChanged(SIMStatus::Status status);
    void statusComplete(SIMStatus::Status status, SIMError error);
};
} // namespace SIM

}
#endif
