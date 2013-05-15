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

#include "timezoneview.h"

TimeZoneView::TimeZoneView(QGraphicsWidget *parent) :
    m_TextEdit(0),
    m_TextEditShowsHint(false),
    m_List(0),
    m_SelectedItem(0),
    m_CellCreator(0),
    proxyModel(0)
{
   Q_UNUSED(parent);

}

TimeZoneView::~TimeZoneView()
{
}

void TimeZoneView::initWidget()
{
}

void TimeZoneView::finishView()
{
}

void TimeZoneView::hideEmptyTextEdit(){}
bool TimeZoneView::isViewCreated()
{
    return true;
}

QString TimeZoneView::title() const
{
    return QString();
}

void TimeZoneView::displayEnteredSlot()
{
}

void TimeZoneView::scrollToSelected()
{
}

void TimeZoneView::liveFilteringTextChangedSlot()
{
}

void TimeZoneView::filteringVKBSlot()
{
}

void TimeZoneView::showTextEdit(bool show) 
{
    Q_UNUSED(show);
}

void TimeZoneView::itemClickedSlot(const QModelIndex &index)
{
    Q_UNUSED(index);
}

void TimeZoneView::retranslateUi()
{
}

bool TimeZoneView::back()
{
    return true;
}

#ifdef TWO_COLUMN_IN_LANDSCAPE
void TimeZoneView::pageRotated(const M::Orientation &orientation)
{
    Q_UNUSED(orientation);
}
#endif



