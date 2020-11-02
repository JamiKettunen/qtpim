/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtContacts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QDECLARATIVECONTACTFAMILY_H
#define QDECLARATIVECONTACTFAMILY_H

#include <QtContacts/qcontactfamily.h>

#include "qdeclarativecontactdetail_p.h"

QTCONTACTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE

class QDeclarativeContactFamily : public QDeclarativeContactDetail
{
    Q_OBJECT
    Q_PROPERTY(QString spouse READ spouse WRITE setSpouse NOTIFY valueChanged)
    Q_PROPERTY(QStringList children READ children WRITE setChildren NOTIFY valueChanged)
    Q_ENUMS(FieldType)
public:
    enum FieldType {
        Spouse = QContactFamily::FieldSpouse,
        Children = QContactFamily::FieldChildren
    };
    QDeclarativeContactFamily(QObject* parent = nullptr)
        :QDeclarativeContactDetail(parent)
    {
        setDetail(QContactFamily());
        connect(this, SIGNAL(valueChanged()), SIGNAL(detailChanged()));
    }
    DetailType detailType() const
    {
        return QDeclarativeContactDetail::Family;
    }

    void setSpouse(const QString& v)
    {
        if (!readOnly() && v != spouse()) {
            detail().setValue(QContactFamily::FieldSpouse, v);
            emit valueChanged();
        }
    }
    QString spouse() const {return detail().value(QContactFamily::FieldSpouse).toString();}
    void setChildren(const QStringList& v)
    {
        if (!readOnly() && QSet<QString>(v.constBegin(), v.constEnd()) != QSet<QString>(children().constBegin(), children().constEnd())) {
            detail().setValue(QContactFamily::FieldChildren, v);
            emit valueChanged();
        }
    }
    QStringList children() const {return detail().value<QStringList>(QContactFamily::FieldChildren);}
signals:
    void valueChanged();
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QDeclarativeContactFamily)

#endif // QDECLARATIVECONTACTFAMILY_H
