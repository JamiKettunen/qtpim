/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: http://www.qt-project.org/
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QCONTACTFETCHBYIDREQUEST_H
#define QCONTACTFETCHBYIDREQUEST_H

#include <qcontactsglobal.h>
#include <qcontactabstractrequest.h>
#include <qcontact.h>
#include <qcontactfetchhint.h>

#include <QList>
#include <QStringList>

QTCONTACTS_BEGIN_NAMESPACE

class QContactFetchByIdRequestPrivate;
class Q_CONTACTS_EXPORT QContactFetchByIdRequest : public QContactAbstractRequest
{
    Q_OBJECT

public:
    QContactFetchByIdRequest(QObject* parent = 0);
    ~QContactFetchByIdRequest();

    /* Selection, restriction and sorting */
    void setIds(const QList<QContactId>& ids);
    void setFetchHint(const QContactFetchHint& fetchHint);
    QList<QContactId> contactIds() const;
    QContactFetchHint fetchHint() const;

    /* Results */
    QList<QContact> contacts() const;
    QMap<int, QContactManager::Error> errorMap() const;

private:
    Q_DISABLE_COPY(QContactFetchByIdRequest)
    friend class QContactManagerEngine;
    Q_DECLARE_PRIVATE_D(d_ptr, QContactFetchByIdRequest)
};

QTCONTACTS_END_NAMESPACE

#endif
