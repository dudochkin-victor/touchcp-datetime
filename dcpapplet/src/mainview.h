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

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <DcpStylableWidget> 

#include "settings.h"
#include "viewid.h"

class MButton;
class MButtonGroup;
class MLayout;
class MLinearLayoutPolicy;
class MGridLayoutPolicy;
class MLabel;
class MLocale;
class DrillListItem;
class MComboBox;

class AutoSyncButton;

class MainView : public DcpStylableWidget {
    Q_OBJECT

    enum TimeFormatCBoxIndex {
        TimeFormatCBoxIndexInvalid = -1,
        TimeFormatCBoxIndex12h = 0,    
        TimeFormatCBoxIndex24h
    };

    enum ClockTypeCBoxIndex {
        ClockTypeCBoxIndexInvalid = -1,
        ClockTypeCBoxIndexAnalog = 0,    
        ClockTypeCBoxIndexDigital
    };
    public:
        MainView(QGraphicsWidget *parent=0);
        virtual ~MainView();
        virtual bool back();
    	bool isViewCreated();

    signals:
        void refererToChangeWidget(View::Id);

    protected:
        void initWidget();
        QString title() const;
        virtual void retranslateUi();

    private:
        void setupItem(DrillListItem *item, QString title, QString subtitle);
        MLayout *m_ButtonsLayout;
        MGridLayoutPolicy *m_ButtonsHLayoutPolicy;
        MLinearLayoutPolicy *m_ButtonsVLayoutPolicy;
        DrillListItem *m_DateButton;
        DrillListItem *m_TimeButton;
        MButtonGroup* m_ButtonGroup;
        MComboBox *m_TimeFormatCBox;
        MComboBox *m_ClockTypeCBox;
        DrillListItem *m_TimeZoneButton;
        AutoSyncButton *m_AutoSyncButton;
        MLocale *m_Locale;
    	bool m_IsViewCreated;
    private slots:
        void showTimeZoneView();
        void updateTimeText();
        void updateDateText();
        void updateTimeZoneText();
        void updateTimeFormatText();
        void updateClockTypeText();
        void showDateView();
        void showTimeView();
        void datetimeChangedSlot();
        void datetimeSettingsChangedSlot();
        void timeFormatCBoxActivatedSlot(int idx);
        void clockTypeCBoxActivatedSlot(int idx);
        void mlocaleSettingsChanged();
        void finishMainView();
        friend class Ut_MainView;
};

#endif

