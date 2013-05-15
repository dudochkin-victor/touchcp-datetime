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

#include "timeview.h"


TimeView::TimeView(QGraphicsWidget *parent) :
    m_TimePicker(0),
    m_DigitalTime(0),
    m_BlockInfiniteTimeChangeLoop(false)
{
    Q_UNUSED(parent);
}

bool TimeView::back()
{
    return true;
}

void TimeView::initWidget()
{
}

bool TimeView::isViewCreated()
{
    return true;
}

void TimeView::finishView() {}

QString TimeView::title() const
{
    return QString();
}

void TimeView::enterDisplayEvent()
{
}

void TimeView::retranslateUi()
{
}

void TimeView::pickerTimeChangedSlot(int hour, int min)
{
    Q_UNUSED(hour);
    Q_UNUSED(min);
}

void TimeView::digitalTimeChangedSlot()
{
}

void TimeView::timeOrDateChangedSlot()
{
}
