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
#include <datetimetextedit.h>
#include <QDateTime>

class FakeData
{
public:
    FakeData()
        {dt =  QDateTime::currentDateTime();}
    QDateTime dt;
};

static FakeData fakeData;

DateTimeTextEdit::DateTimeTextEdit() : d_ptr(0) {}
DateTimeTextEdit::DateTimeTextEdit(const QDateTime& , DisplayMode ) : d_ptr(0){}
DateTimeTextEdit::~DateTimeTextEdit(){}
const QDateTime& DateTimeTextEdit::time(){
    return fakeData.dt;
}

void DateTimeTextEdit::setTime(const QDateTime& dt){fakeData.dt = dt;}
bool DateTimeTextEdit::isClock12h() { return true; }
bool DateTimeTextEdit::isAm() { return true; }
bool DateTimeTextEdit::setAm(bool ) { return true; }
int DateTimeTextEdit::minimumYear() { return 2010; }
void DateTimeTextEdit::setMinimumYear(int ){}
int DateTimeTextEdit::maximumYear() { return 2100; }
void DateTimeTextEdit::setMaximumYear(int ){}
void DateTimeTextEdit::cursorPositionChanged(int ){}
void DateTimeTextEdit::keyPressEvent(QKeyEvent* ){}
void DateTimeTextEdit::gainedFocusSlot(){}
void DateTimeTextEdit::lostFocusSlot(){}
void DateTimeTextEdit::localeSettingsChanged(){}
void DateTimeTextEdit::qmTimeOrSettingsChanged(){}
void DateTimeTextEdit::doPostInitialization(){}

