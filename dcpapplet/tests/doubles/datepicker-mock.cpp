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
#ifdef HAVE_DATEPICKER
#include "datepicker.h"
#else
#include "datepicker-fake.h"

#include <MTextEdit>
#include <MComboBox>
DateTimePanel::DateTimePanel(): MWidget()
{
}

DateTimePanel::DateTimePanel(const QDateTime& time,
                             MLocale::DateType, MLocale::TimeType):
    MWidget(),
    m_time(time)
{
}

DateTimePanel::~DateTimePanel()
{
}

void DateTimePanel::setTimeStyle(const QString)
{

}

void DateTimePanel::setAmStyle(const QString)
{

}

void DateTimePanel::setPmStyle(const QString)
{

}

void DateTimePanel::initWidget (MLocale::DateType,
                                MLocale::TimeType)
{
}

MTextEdit* DateTimePanel::createNumberEdit()
{
    MTextEdit* edit = new MTextEdit();
    edit->setContentType (M::NumberContentType);
    connect(edit, SIGNAL(lostFocus(Qt::FocusReason)),
            this, SLOT(validateTime()));
    return edit;
}

MComboBox* DateTimePanel::createNumberCombo(int upper, int lower)
{
   MComboBox *combo = new MComboBox();
   for (int i=lower; i < upper; i++)
	combo->addItem(QString::number(i));
   connect(combo, SIGNAL(lostFocus(Qt::FocusReason)),
            this, SLOT(validateTime()));
   return combo;
}

void DateTimePanel::validateTime()
{
}

void DateTimePanel::updateTime(void)
{
}

const QDateTime& DateTimePanel::time()
{
    return m_time;
}

void DateTimePanel::setTime(const QDateTime& time)
{
    m_time = time;
    emit timeChanged();
}
#endif

#ifdef HAVE_DATEPICKER
DatePicker::DatePicker(QGraphicsItem*, bool) : d_ptr(0)
{}
DatePicker::DatePicker(const QDate&, const MCalendar&, QGraphicsItem*, bool) : d_ptr(0){}
#else
DatePicker::DatePicker(QGraphicsItem*)
{}
DatePicker::DatePicker(const QDate&, const MCalendar&, QGraphicsItem*){}
#endif
DatePicker::~DatePicker(){}
void DatePicker::updateContent(){}
void DatePicker::setSelectedDay(int, int, int){}
void DatePicker::setEarliestAllowedDay(int, int, int){}
void DatePicker::setLatestAllowedDay(int, int, int){}

#ifndef HAVE_DATEPICKER
void DatePicker::onClicked(const QDate &)
{

}
#endif

