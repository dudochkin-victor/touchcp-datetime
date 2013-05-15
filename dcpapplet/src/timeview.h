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

#ifndef TIMEVIEW_H
#define TIMEVIEW_H

#include <DcpStylableWidget>

class MLabel;
class TimePicker;
class MContainer;
class DcpTime;
class DateTimePanel;

class TimeView : public DcpStylableWidget {
    Q_OBJECT

    public:
        TimeView(QGraphicsWidget *parent = 0);
        virtual bool back();
        virtual bool pagePans() const { return false; }
    	bool isViewCreated();

    protected:
        void initWidget();
        QString title() const;
        virtual void retranslateUi();
        virtual void enterDisplayEvent();

    private slots:
        void timeOrDateChangedSlot();
        void pickerTimeChangedSlot(int hour, int min);
        void digitalTimeChangedSlot();
        void finishView();

    private:
        TimePicker *m_TimePicker;
        DateTimePanel *m_DigitalTime;
        bool m_BlockInfiniteTimeChangeLoop;
    	bool m_IsViewCreated;
        friend class Ut_TimeView;
};


#endif

