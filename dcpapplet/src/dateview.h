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

#ifndef DATEVIEW_H
#define DATEVIEW_H

#include <DcpStylableWidget>

class MLabel;
class MContainer;
class DatePicker;
class DateTimePanel;

class DateView : public DcpStylableWidget {
    Q_OBJECT

    public:
        DateView(QGraphicsWidget *parent = 0);
        virtual ~DateView();

        virtual bool back();
        virtual bool pagePans () const { return false; }
    	bool isViewCreated();

    protected:
        void initWidget();
        QString title() const;
        virtual void retranslateUi();
        virtual void enterDisplayEvent();

    private slots:
        void daySelected(int year, int month, int day);
        void timeOrDateChangedSlot();
        void digitalDateChangedSlot();
        void finishView();

    private:
        int m_Year, m_Month, m_Day;
        DatePicker *m_MonthWidget;
        DateTimePanel *m_DigitalDate;
    	bool m_IsViewCreated;
        friend class Ut_DateView;
};


#endif

