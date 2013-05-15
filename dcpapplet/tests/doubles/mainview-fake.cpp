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
#include "mainview.h"


MainView::MainView(QGraphicsWidget *parent) :
    m_ButtonsLayout(0),
    m_ButtonsHLayoutPolicy(0),
    m_ButtonsVLayoutPolicy(0),
    m_DateButton(0),
    m_TimeButton(0),
    m_ButtonGroup(0),
    m_TimeFormatCBox(0),
    m_TimeZoneButton(0),
    m_AutoSyncButton(0),
    m_Locale(0)
{
   Q_UNUSED(parent);
}

MainView::~MainView()
{
}

bool MainView::back()
{
    return true;
}

void MainView::initWidget()
{
}

QString MainView::title() const
{
    return QString(qtTrId(QtnDateTimeTitle));
}

void MainView::retranslateUi()
{
}

void MainView::updateTimeText()
{
}

void MainView::updateDateText()
{
}

void MainView::updateTimeZoneText()
{
}

void MainView::updateTimeFormatText()
{
}

void MainView::updateClockTypeText()
{
}

void MainView::showDateView()
{
}

void MainView::showTimeView()
{
}

void MainView::showTimeZoneView()
{
}

void MainView::datetimeChangedSlot()
{
}

void MainView::datetimeSettingsChangedSlot()
{
}

void MainView::timeFormatCBoxActivatedSlot(int idx)
{
    Q_UNUSED(idx);
}

void MainView::clockTypeCBoxActivatedSlot(int idx)
{
    Q_UNUSED(idx);
}

void MainView::mlocaleSettingsChanged()
{
}
void MainView::finishMainView(){}

