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

#ifndef TIMEZONECELL_H
#define TIMEZONECELL_H

#include <MBasicListItem>
#include <MLabel>


class TimeZoneCell : public MBasicListItem
{
    Q_OBJECT
    public:
    TimeZoneCell(QGraphicsItem *parent = 0): MBasicListItem(MBasicListItem::TitleWithSubtitle, parent)
    {
        titleLabelWidget()->setStyleName("CommonTitleInverted");
        subtitleLabelWidget()->setStyleName("CommonSubTitleInverted");
        setStyleName("CommonPanelInverted");
    };
};


#endif
