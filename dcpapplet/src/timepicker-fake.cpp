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
#include "timepicker-fake.h"
#include <MWidgetModel>

TimePicker::TimePicker(int, int, MWidget *parent):
    MWidgetController(new MWidgetModel, parent)
{

}

TimePicker::~TimePicker()
{

}

void TimePicker::setMinutes(const int min)
{
    m_minutes = min;
}

int TimePicker::minutes()
{
    return m_minutes;
}

void TimePicker::setHours(const int hours)
{
    m_hours = hours;
}

int TimePicker::hours()
{
    return m_hours;
}

// vim: sw=4 sts=4 et tw=100
