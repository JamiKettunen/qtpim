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

#ifndef QCONTACTABSTRACTREQUEST_H
#define QCONTACTABSTRACTREQUEST_H

#include <qcontactmanager.h>
#include <QObject>

QTCONTACTS_BEGIN_NAMESPACE

class QContactManagerEngine;
class QContactAbstractRequestPrivate;
class Q_CONTACTS_EXPORT QContactAbstractRequest : public QObject
{
    Q_OBJECT

public:
    ~QContactAbstractRequest();

    Q_ENUMS(State)
    enum State {
        InactiveState = 0,   // operation not yet started
        ActiveState,         // operation started, not yet finished
        CanceledState,       // operation is finished due to cancellation
        FinishedState        // operation either completed successfully or failed.  No further results will become available.
    };

    State state() const; // replaces status()
    bool isInactive() const;
    bool isActive() const;
    bool isFinished() const;
    bool isCanceled() const;
    QContactManager::Error error() const;

    Q_ENUMS(RequestType)
    enum RequestType {
        InvalidRequest = 0,
        ContactFetchRequest,
        ContactIdFetchRequest,
        ContactRemoveRequest,
        ContactSaveRequest,
        DetailDefinitionFetchRequest,
        DetailDefinitionRemoveRequest,
        DetailDefinitionSaveRequest,
        RelationshipFetchRequest,
        RelationshipRemoveRequest,
        RelationshipSaveRequest,
        ContactFetchByIdRequest
    };

    RequestType type() const;

    /* Which manager we want to perform the asynchronous request */
    QContactManager* manager() const;
    void setManager(QContactManager* manager);

public Q_SLOTS:
    /* Verbs */
    bool start();
    bool cancel();

    /* waiting for stuff */
    bool waitForFinished(int msecs = 0);

Q_SIGNALS:
    void stateChanged(QContactAbstractRequest::State newState);
    void resultsAvailable();

protected:
    QContactAbstractRequest(QContactAbstractRequestPrivate* otherd, QObject* parent = 0);
    QContactAbstractRequestPrivate* d_ptr;

private:
    QContactAbstractRequest(QObject* parent = 0) : QObject(parent), d_ptr(0) {}
    Q_DISABLE_COPY(QContactAbstractRequest)
    friend class QContactManagerEngine;
    friend class QContactManagerEngineV2;
    friend class QContactManagerEngineV2Wrapper;
    friend class QContactAbstractRequestPrivate;

#ifndef QT_NO_DEBUG_STREAM
    Q_CONTACTS_EXPORT friend QDebug operator<<(QDebug dbg, const QContactAbstractRequest& request);
#endif

};


QTCONTACTS_END_NAMESPACE

#endif
