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

#include "translation.h"
#include "dateview.h"

#include "debug.h"


DateView::DateView(QGraphicsWidget *parent) :
        m_Year(1), m_Month(1), m_Day(1),
        m_MonthWidget(0),
        m_DigitalDate(0)
{
    Q_UNUSED(parent);
}

DateView::~DateView()
{
}

bool DateView::back()
{
    return true;
}

void DateView::retranslateUi()
{
}

void DateView::initWidget()
{
}

void DateView::finishView() {}

bool DateView::isViewCreated()
{
    return true;
}
QString DateView::title() const
{
    return QString(qtTrId(QtnCommTimeDatepickerTitle));
}

void DateView::enterDisplayEvent()
{
}

void DateView::daySelected(int year, int month, int day)
{
    Q_UNUSED(year);
    Q_UNUSED(month);
    Q_UNUSED(day);
}
void DateView::digitalDateChangedSlot()
{
}

void DateView::timeOrDateChangedSlot()
{
}


