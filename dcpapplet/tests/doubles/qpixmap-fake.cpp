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

#include <QPaintDevice>
#include <QPixmap>
class Ref{
	public: bool deref() {return false;}
};
class QPixmapData{ public: Ref ref;};
QPixmap::QPixmap(): QPaintDevice(){}
QPaintDevice::QPaintDevice(){};
QPixmap::~QPixmap(){}
QPixmap::QPixmap(int, int): QPaintDevice(){}
//QPixmap::QPixmap(const QString &, const char *, 
//                 Qt::ImageConversionFlags){}
//QPixmap::QPixmap ( const char * const[] xpm ){}
//QPixmap::QPixmap ( const QPixmap &): QPaintDevice(){}
//QPixmap::QPixmap ( const QSize &){}

