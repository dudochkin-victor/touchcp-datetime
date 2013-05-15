/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
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
#include "drilllistitem.h"

#include <QtGui/QGraphicsGridLayout>

#include <MImageWidget>
#include <MLabel>
#include <MImageWidget>


DrillListItem::DrillListItem (QGraphicsWidget *parent)
    : MBasicListItem(MBasicListItem::TitleWithSubtitle, parent)
{
    setStyleName("CommonPanelInverted");
}

DrillListItem::~DrillListItem()
{
}

QGraphicsLayout *DrillListItem::createLayout()
{
    QGraphicsGridLayout *layout = new QGraphicsGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    titleLabelWidget()->setStyleName("CommonTitleInverted");
    layout->addItem(titleLabelWidget(), 0, 1);
    layout->setAlignment(titleLabelWidget(), Qt::AlignTop | Qt::AlignLeft);

    subtitleLabelWidget()->setStyleName("CommonSubTitleInverted");
    layout->addItem(subtitleLabelWidget(), 1, 1);

    MImageWidget *drillImage = new MImageWidget("icon-m-common-drilldown-arrow", this);
    drillImage->setStyleName("CommonDrillDownIcon");
    layout->addItem(drillImage, 0, 2, 2, 1);
    layout->setAlignment(drillImage, Qt::AlignVCenter | Qt::AlignRight);

    return layout;
}

void DrillListItem::setDisabled(bool disable)
{
    setEnabled(!disable);
    titleLabelWidget()->setStyleName("CommonTitleInverted");
    subtitleLabelWidget()->setStyleName("CommonSubTitleInverted");
}
