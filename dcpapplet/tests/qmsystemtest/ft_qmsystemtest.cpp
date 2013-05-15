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
#include "ft_displaylangapplet.h"

#include <dcpappletmetadata.h>
#include <dcpappletplugin.h>

void Ft_DisplayLangApplet::testAppletIsLoadable()
{
    DcpAppletMetadata metadata("/dev/null");
    printf("Checking lib at %s \n" , qPrintable(metadata.fullBinary()));
    DcpAppletPlugin loader(&metadata);
    QVERIFY(loader.applet());
}

QTEST_APPLESS_MAIN(Ft_DisplayLangApplet)

