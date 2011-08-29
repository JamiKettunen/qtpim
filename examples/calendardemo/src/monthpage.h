/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MONTHPAGE_H_
#define MONTHPAGE_H_

#include <QWidget>
#include <QDate>
#include <qtorganizerglobal.h>

QTPIM_BEGIN_NAMESPACE
class QOrganizerManager;
class QOrganizerItem;
QTPIM_END_NAMESPACE
QTPIM_USE_NAMESPACE

class QComboBox;
class QCalendarWidget;
class QLabel;
class QListWidget;
class QListWidgetItem;
class QMenu;

class MonthPage : public QWidget
{
    Q_OBJECT

public:
    MonthPage(QWidget *parent = 0);
    ~MonthPage();
    void init();

#ifdef Q_OS_SYMBIAN
    void setMenu(QMenu *menu);
#endif

private Q_SLOTS:
    void backendChanged(const QString &managerName);
    void refreshDayItems();
    void currentMonthChanged();
    void dayDoubleClicked(QDate date);
    void openDay();
    void itemDoubleClicked(QListWidgetItem *listItem);

public Q_SLOTS:
    void editItem();
    void removeItem();
    void refresh();

Q_SIGNALS:
    void managerChanged(QOrganizerManager *manager);
    void currentDayChanged(QDate date);
    void showDayPage(QDate date);
    void showEditPage(const QOrganizerItem &item);
    void addNewEvent();
    void addNewTodo();
    
protected: // from QWidget
    void showEvent(QShowEvent *event);

private:
    QComboBox* m_managerComboBox;
    QOrganizerManager *m_manager;
    QCalendarWidget *m_calendarWidget;
    QLabel *m_dateLabel;
    QListWidget *m_itemList;
    bool m_ignoreShowDayPageOnceFlag;
};

#endif // MONTHPAGE_H_
