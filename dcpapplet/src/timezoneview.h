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

#ifndef TIMEZONEVIEW_H
#define TIMEZONEVIEW_H

#define QUICKSEARCH
/*#undef QUICKSEARCH*/

#include <DcpStylableWidget>

class MTextEdit;
class MList;
class QModelIndex;
class QItemSelectionModel;

class TimeZoneView : public DcpStylableWidget {
    Q_OBJECT

    public:
        TimeZoneView(QGraphicsWidget *parent = 0);
        virtual ~TimeZoneView();
    	bool isViewCreated();

    public slots:
        bool back();

    private:
        void initWidget();
        QString title() const;
        void showTextEdit(bool show);

    private slots:
        void displayEnteredSlot();
        void scrollToSelected();
        void itemClickedSlot(const QModelIndex &index);
        void liveFilteringTextChangedSlot();
        void filteringVKBSlot();

        void retranslateUi();
#ifdef TWO_COLUMN_IN_LANDSCAPE
        void pageRotated(const M::Orientation &orientation);
#endif
        void finishView();
	void hideEmptyTextEdit();

    private:
        QModelIndex translateModelIndex(const QModelIndex &timezoneModelIndex);

        MTextEdit *m_TextEdit;
        bool m_TextEditShowsHint;
        MList *m_List;
        int m_SelectedItem;
        class TimezoneContentItemCreator * m_CellCreator;
        class MSortFilterProxyModel *proxyModel;
    	bool m_IsViewCreated;
};

#endif


