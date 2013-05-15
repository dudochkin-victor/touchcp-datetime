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
#ifndef TIMEPICKER_FAKE_H
#define TIMEPICKER_FAKE_H
#include <MWidgetController>

class TimePicker : public MWidgetController
{
    Q_OBJECT

  public:
    explicit TimePicker ( int hours = 7, int minutes = 0, MWidget *parent = 0 );
    ~TimePicker ();
    void setMinutes(const int minutes);
    int minutes();
    void setHours(const int hours);
    int hours();
  signals:
    void timeChanged(int hours, int minutes);
private:
    int m_minutes;
    int m_hours;
};

#endif

