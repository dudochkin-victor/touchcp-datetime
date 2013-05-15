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
#ifndef DATEPICKER_FAKE_H
#define DATEPICKER_FAKE_H

#include <MLocale>
#include <MCalendar>
#include <MWidgetController>
#include <QObject>
#include <QtCore/QDateTime>
#include <QGraphicsProxyWidget>

class MTextEdit;
class MComboBox;

class DateTimePanel : public MWidget
{
  Q_OBJECT

public:
  DateTimePanel();
  DateTimePanel(const QDateTime& time, MLocale::DateType dateType,
                MLocale::TimeType timeType);
  ~DateTimePanel();
  const QDateTime& time();
  void setTime(const QDateTime& time);
  void setTimeStyle(const QString style);
  void setAmStyle(const QString style);
  void setPmStyle(const QString style);

private:
  void initWidget(MLocale::DateType dtype = MLocale::DateShort,
                  MLocale::TimeType ttype = MLocale::TimeShort);
  void updateTime();
  MTextEdit* createNumberEdit();
  MComboBox* createNumberCombo(int upper, int lower=0);

signals:
  void timeChanged();

private slots:
    void validateTime();

private:
  MTextEdit *m_yearEdit;
  MTextEdit *m_monthEdit;
  MTextEdit *m_dayEdit;
  MComboBox *m_hourEdit;
  MComboBox *m_minuteEdit;
  QDateTime m_time;
};


class DatePicker : public QGraphicsProxyWidget
{
  Q_OBJECT

public:
  DatePicker(QGraphicsItem* parent = 0);
  DatePicker(const QDate& date, const MCalendar& calendar = MCalendar(), QGraphicsItem* parent = 0);
  DatePicker(const MCalendar& cal);
  ~DatePicker();
  void updateContent();
  void dayChanged();
  void setSelectionSupported(bool value);
  void setSelectedDay(int year, int month, int day);
  void setEarliestAllowedDay(int, int, int);
  void setLatestAllowedDay(int, int, int);
signals:
  void daySelected(int year, int month, int day);

protected slots:
  void onClicked(const QDate & date);

protected:
  void setSelectedDate(const QDate& date);

private:
  void construct(const MCalendar& cal);
  class QCalendarWidget* m_Calendar;
};

#endif

