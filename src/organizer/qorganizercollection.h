/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
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

#ifndef QORGANIZERCOLLECTION_H
#define QORGANIZERCOLLECTION_H

#include <QVariantMap>
#include <QVariant>
#include <QString>
#include <QList>
#include <QSharedDataPointer>

#include <qorganizeritemid.h>
#include <qorganizercollectionid.h>

QTORGANIZER_BEGIN_NAMESPACE

class QOrganizerManagerEngine;
class QOrganizerCollectionData;
class Q_ORGANIZER_EXPORT QOrganizerCollection
{
public:
    QOrganizerCollection();

    ~QOrganizerCollection();

    QOrganizerCollection(const QOrganizerCollection& other);
    QOrganizerCollection& operator=(const QOrganizerCollection& other);

    bool operator==(const QOrganizerCollection &other) const;
    bool operator!=(const QOrganizerCollection &other) const {return !(other == *this);}

    /* Every collection has an id */
    QOrganizerCollectionId id() const;
    void setId(const QOrganizerCollectionId& id);

    void setMetaData(const QVariantMap& metaData);
    QVariantMap metaData() const;

    void setMetaData(const QString& key, const QVariant& value);
    QVariant metaData(const QString& key) const;

    /* Default meta data keys */
    const static QString KeyName;
    const static QString KeyDescription;
    const static QString KeyColor;
    const static QString KeyImage;

private:
    friend class QOrganizerManagerEngine;
    QSharedDataPointer<QOrganizerCollectionData> d;
};

Q_ORGANIZER_EXPORT uint qHash(const QOrganizerCollection& key);
#ifndef QT_NO_DEBUG_STREAM
Q_ORGANIZER_EXPORT QDebug operator<<(QDebug dbg, const QOrganizerCollection& collection);
#endif

#ifndef QT_NO_DATASTREAM
Q_ORGANIZER_EXPORT QDataStream& operator<<(QDataStream& out, const QOrganizerCollection& collection);
Q_ORGANIZER_EXPORT QDataStream& operator>>(QDataStream& in, QOrganizerCollection& collection);
#endif

QTORGANIZER_END_NAMESPACE

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO(QTORGANIZER_PREPEND_NAMESPACE(QOrganizerCollection), Q_MOVABLE_TYPE);
QT_END_NAMESPACE

#endif

