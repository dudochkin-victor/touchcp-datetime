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
#include "datepicker-fake.h"
#include <QDebug>
#include <MWidgetModel>
#include <MLabel>
#include <MTextEdit>
#include <MComboBox>
#include <MLayout>
#include <MLinearLayoutPolicy>

#include <QGraphicsLinearLayout>
#include <QGraphicsProxyWidget>
#include <QCalendarWidget>
#include <MTheme>
#include <mdefaultfonts.h>

DateTimePanel::DateTimePanel(): MWidget()
{
    m_time = QDateTime::currentDateTime();
    initWidget();
    updateTime();
}

DateTimePanel::DateTimePanel(const QDateTime& time,
                             MLocale::DateType dtype, MLocale::TimeType ttype):
    MWidget(),
    m_time(time)
{
    initWidget(dtype, ttype);
    updateTime();
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

void DateTimePanel::initWidget (MLocale::DateType dtype,
                                MLocale::TimeType ttype)
{
    m_yearEdit = m_monthEdit = m_dayEdit = 0;
    m_hourEdit = m_minuteEdit = 0;

    MLayout *mainLayout = new MLayout(this);
    MLinearLayoutPolicy *mPolicy =
        new MLinearLayoutPolicy(mainLayout, Qt::Horizontal);
    mainLayout->setPolicy(mPolicy);

    if (dtype != MLocale::DateNone) {
        m_yearEdit = createNumberEdit();
        m_monthEdit = createNumberEdit();
        m_dayEdit = createNumberEdit();

        mPolicy->addItem(m_yearEdit);
        mPolicy->addItem(m_monthEdit);
        mPolicy->addItem(m_dayEdit);
    }

    if (ttype != MLocale::TimeNone) {
        MLabel *timeSeparatorLabel = new MLabel(":");
        m_hourEdit = createNumberCombo(24);
        m_minuteEdit = createNumberCombo(60);

        mPolicy->addItem(m_hourEdit);
        mPolicy->addItem(timeSeparatorLabel);
        mPolicy->addItem(m_minuteEdit);
    }

    setLayout(mainLayout);
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
   connect(combo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(validateTime()));
   return combo;
}

void DateTimePanel::validateTime()
{
    bool hasTimeChanged = false;

    if (m_yearEdit) {
        Q_ASSERT (m_monthEdit);
        Q_ASSERT (m_dayEdit);

        QDate newDate;
        bool yearOK, monthOK, dayOK;
        newDate.setDate(m_yearEdit->text().toInt(&yearOK),
                        m_monthEdit->text().toInt(&monthOK),
                        m_dayEdit->text().toInt(&dayOK));
        if (yearOK && monthOK && dayOK && newDate.isValid()) {
            qDebug("Valid!!!");
            m_time.setDate(newDate);
            hasTimeChanged = true;
        } else {
            qDebug("Not valid :(");
        }
    }

    if (m_hourEdit) {
        Q_ASSERT (m_minuteEdit);
        QTime newTime;
        bool hourOK, minOK;
        newTime.setHMS(m_hourEdit->currentText().toInt(&hourOK),
                       m_minuteEdit->currentText().toInt(&minOK),0);
        if (hourOK && minOK && newTime.isValid()) {
            qDebug("Valid!!!");
            m_time.setTime(newTime);
            hasTimeChanged = true;
        } else {
            qDebug("Not valid :(");
        }
    }

    if (hasTimeChanged) {
        emit timeChanged();
    }
    updateTime();
}

void DateTimePanel::updateTime(void)
{
    if (m_yearEdit) {
        m_yearEdit->setText(m_time.toString("yyyy"));
    }
    if (m_monthEdit) {
        m_monthEdit->setText(m_time.toString("MM"));
    }
    if (m_dayEdit) {
        m_dayEdit->setText(m_time.toString("dd"));
    }
    if (m_hourEdit) {
        m_hourEdit->setCurrentIndex(m_time.time().hour());
    }
    if (m_minuteEdit) {
        m_minuteEdit->setCurrentIndex(m_time.time().minute());
    }
}

const QDateTime& DateTimePanel::time()
{
    return m_time;
}

void DateTimePanel::setTime(const QDateTime& time)
{
    m_time = time;
    updateTime();
    emit timeChanged();
}





DatePicker::DatePicker(QGraphicsItem*)
{
    construct(MCalendar());
}

DatePicker::DatePicker(const QDate& date, const MCalendar& cal, QGraphicsItem*)
{
    construct (cal);
    m_Calendar->setSelectedDate (date);
}

DatePicker::DatePicker(const MCalendar& cal)
{
    construct (cal);
}

void
DatePicker::construct(const MCalendar& cal)
{
    m_Calendar = new QCalendarWidget ();
    m_Calendar->setGridVisible (true);
    m_Calendar->setFirstDayOfWeek ((Qt::DayOfWeek) cal.firstDayOfWeek());
    m_Calendar->setMaximumDate (QDate(2100,1,1));
    m_Calendar->setMinimumDate (QDate());
    m_Calendar->setNavigationBarVisible (true);
    m_Calendar->setDateEditEnabled (false);
    connect (m_Calendar, SIGNAL (clicked (QDate)),
             this, SLOT (onClicked (QDate)));

    // this hack disables opening of the month and year buttons:
    QWidget* monthButton =
        m_Calendar->findChild<QWidget*>("qt_calendar_monthbutton");
    QWidget* yearButton =
        m_Calendar->findChild<QWidget*>("qt_calendar_yearbutton");
    monthButton->setEnabled (false);
    yearButton->setEnabled (false);

    setWidget (m_Calendar);
    setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
}

DatePicker::~DatePicker()
{
}

void
DatePicker::onClicked ( const QDate & date )
{
    if (date.isValid()) {
        dayChanged ();
    }
}

void DatePicker::setEarliestAllowedDay(int, int, int){}
void DatePicker::setLatestAllowedDay(int, int, int){}

void DatePicker::updateContent()
{
}

void DatePicker::dayChanged()
{
    QDate date = m_Calendar->selectedDate();
    emit daySelected(date.year(), date.month(), date.day());
}

void DatePicker::setSelectionSupported(bool)
{
    // unfortunately it is not supported
}

void DatePicker::setSelectedDay(int year, int month, int day)
{
    setSelectedDate (QDate (year, month, day));
}

void DatePicker::setSelectedDate (const QDate& date)
{
    m_Calendar->setSelectedDate (date);
}

//vim: sw=4 sts=4 et tw=100

