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

#include <MTheme>

MTheme::MTheme(const QString&, const QString&, ThemeService) : d_ptr(0) {};
const QPixmap * MTheme::pixmap (
        const QString &, const QSize &)
{
    return (QPixmap*)1; // !!! please do not use this pixmap ever
                        // it is an easy solution to avoid running
                        // QPixmap's constructor which requires
                        // a QApplication which requires X
}

void MTheme::releasePixmap (const QPixmap *)
{
}
 
// static

bool MTheme::loadCSS(const QString &filename, InsertMode mode)    
{
    Q_UNUSED(filename);
    Q_UNUSED(mode);
    return true;
}

MWidgetView *MTheme::view(const MWidgetController *controller) 
{
    Q_UNUSED(controller);
    return 0;
}
