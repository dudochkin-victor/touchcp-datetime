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

#include <QGraphicsLinearLayout>
#include <QTimer>

#include <MLabel>
#include <MButton>
#include <MBanner>
#include <QtGui/QGraphicsLinearLayout>

#include "translation.h"
#include "autosyncbutton.h"
#include "settings.h"

#include "debug.h"
#include <QDebug>

static const int g_NotificationTimeout = 3000; /* 3 seconds */

AutoSyncButton::AutoSyncButton(MWidget *parent)
             :MStylableWidget(parent)
{
    setObjectName("AutoSyncButton");
    setStyleName("CommonPanelInverted");
    m_BlockSettingAutoSync = 0;
    initWidget();
    QTimer::singleShot(0, this, SLOT(finishWidget()));

}

AutoSyncButton::~AutoSyncButton()
{
}

void AutoSyncButton::retranslateUi()
{
    m_AutomaticLabel->setText(qtTrId(QtnDateAutomaticUpdate));
}

void AutoSyncButton::initWidget()
{
    /* automaticLabel */
    m_AutomaticLabel = new MLabel();
    m_AutomaticLabel->setObjectName("AutoSyncLabel");
    m_AutomaticLabel->setStyleName("CommonSingleTitleInverted");

    /* switchButton */
    m_SwitchButton = new MButton();
    m_SwitchButton->setObjectName("AutoSyncToggleButton");
    m_SwitchButton->setCheckable(true);
    m_SwitchButton->setStyleName("CommonRightSwitchInverted");
    m_SwitchButton->setViewType(MButton::switchType);

}

void AutoSyncButton::finishWidget()
{
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(Qt::Horizontal, this);
    layout->setContentsMargins(0, 0, 20, 0);
    setLayout(layout);
    layout->addItem(m_AutomaticLabel);
    layout->addItem(m_SwitchButton);
    layout->setAlignment(m_AutomaticLabel, Qt::AlignVCenter);
    layout->setAlignment(m_SwitchButton, Qt::AlignVCenter);
    m_BlockSettingAutoSync++;
    m_SwitchButton->setChecked(Settings::instance().getAutoSync());
    m_BlockSettingAutoSync--;
    connect(m_SwitchButton, SIGNAL(toggled(bool)),
            this, SLOT(toggledSlot(bool)));
    connect(m_SwitchButton, SIGNAL(toggled(bool)),
            this, SIGNAL(toggled(bool)));
    connect(&Settings::instance(), SIGNAL(datetimeSettingsChanged()),
            this, SLOT(datetimeSettingsChangedSlot()));

    retranslateUi();


}
void AutoSyncButton::toggledSlot(bool checked)
{
    Settings &s = Settings::instance();
    if(!m_BlockSettingAutoSync){
        if(!s.setAutoSync(checked)){
        if(checked){
            if(!s.isSimInserted()){
                MBanner* infoBanner = new MBanner();
                infoBanner->appear(MSceneWindow::DestroyWhenDone);
                infoBanner->setTitle(qtTrId(QtnDateNoSim));
                infoBanner->setStyleName("InformationBanner");
            } else {
                MBanner* infoBanner = new MBanner();
                infoBanner->appear(MSceneWindow::DestroyWhenDone);
                infoBanner->setTitle(qtTrId(QtnDateTryLater));
                infoBanner->setStyleName("InformationBanner");
            }
            m_SwitchButton->setChecked(false);
        }
        }
        qDebug() << "toggled" << (checked ? "on" : "off");
        //datetimeSettingsChangedSlot();
    }
}

void AutoSyncButton::datetimeSettingsChangedSlot()
{
    m_BlockSettingAutoSync++;
    m_SwitchButton->setChecked(Settings::instance().getAutoSync());
    m_BlockSettingAutoSync--;
}


