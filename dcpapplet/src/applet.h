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

#ifndef APPLET_H
#define APPLET_H

#include <DcpAppletIf>
#include <QObject>
#include <QMap>

#include "viewid.h"

class DcpStylableWidget;
class MAction;

class Applet : public QObject, public DcpAppletIf {
    public:
        Q_OBJECT;
        Q_INTERFACES(DcpAppletIf);

    public:
        virtual void init();
        virtual DcpStylableWidget* constructStylableWidget(int viewId);
        virtual QString title() const;
        virtual QVector<MAction *> viewMenuItems();
        virtual DcpBrief* constructBrief(int partID = 0);

        virtual int partID(const QString& part);

    private slots:
        void refererToChangeWidgetSlot(View::Id);
        void finishCreation();
    private:
        View::Id m_LastConstructedView;
        View::Id m_RefererPage;
        friend class Ut_Applet;
};

#endif

