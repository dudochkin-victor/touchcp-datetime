/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel-languageapplet.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/
#ifndef FT_DISPLAYLANGAPPLET_H
#define FT_DISPLAYLANGAPPLET_H

#include <QtTest/QtTest>
#include <QObject>

class Ft_DisplayLangApplet: public QObject
{
    Q_OBJECT

private slots:
    void testAppletIsLoadable();
};


#endif // FT_DISPLAYLANGAPPLET

