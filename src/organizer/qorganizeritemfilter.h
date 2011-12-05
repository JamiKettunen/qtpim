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

#ifndef QORGANIZERITEMFILTER_H
#define QORGANIZERITEMFILTER_H

#include <QVariant>
#include <QList>
#include <QDateTime>
#include <QSharedData>

#include "qorganizerglobal.h"

QT_BEGIN_NAMESPACE
class QDataStream;
QT_END_NAMESPACE

QTORGANIZER_BEGIN_NAMESPACE

/* Manual Q_DECLARE_ORGANIZERITEMFILTER_PRIVATE macro */

#define Q_DECLARE_ORGANIZERITEMFILTER_PRIVATE(Class) \
    inline Class##Private* d_func(); \
    inline const Class##Private* d_func() const; \
    friend class Class##Private;

class QOrganizerItemFilterPrivate;

// MSVC needs the function declared before the friend declaration
class QOrganizerItemFilter;
#ifndef QT_NO_DATASTREAM
Q_ORGANIZER_EXPORT QDataStream& operator<<(QDataStream& out, const QOrganizerItemFilter& filter);
Q_ORGANIZER_EXPORT QDataStream& operator>>(QDataStream& in, QOrganizerItemFilter& filter);
#endif

class Q_ORGANIZER_EXPORT QOrganizerItemFilter
{
public:
    QOrganizerItemFilter();
    ~QOrganizerItemFilter();
    QOrganizerItemFilter(const QOrganizerItemFilter& other);
    QOrganizerItemFilter& operator=(const QOrganizerItemFilter& other);

    enum FilterType {
        InvalidFilter,
        DetailFilter,
        DetailRangeFilter,
        ChangeLogFilter,
        IntersectionFilter,
        UnionFilter,
        IdFilter,
        CollectionFilter,
        DefaultFilter
    };

    FilterType type() const;

    // Qt::MatchFlags don't quite match here
    enum MatchFlag {
        MatchExactly = Qt::MatchExactly,    // 0
        MatchContains = Qt::MatchContains,  // 1
        MatchStartsWith = Qt::MatchStartsWith,  // 2
        MatchEndsWith = Qt::MatchEndsWith, // 3
        MatchFixedString = Qt::MatchFixedString, // 8
        MatchCaseSensitive = Qt::MatchCaseSensitive // 16
    };
    Q_DECLARE_FLAGS(MatchFlags, MatchFlag)

    bool operator==(const QOrganizerItemFilter& other) const;
    bool operator!=(const QOrganizerItemFilter& other) const {return !operator==(other);}

protected:
    explicit QOrganizerItemFilter(QOrganizerItemFilterPrivate* d);

protected:
    friend class QOrganizerItemFilterPrivate;
#ifndef QT_NO_DATASTREAM
    Q_ORGANIZER_EXPORT friend QDataStream& operator<<(QDataStream& out, const QOrganizerItemFilter& filter);
    Q_ORGANIZER_EXPORT friend QDataStream& operator>>(QDataStream& in, QOrganizerItemFilter& filter);
#endif
#ifndef QT_NO_DEBUG_STREAM
    Q_ORGANIZER_EXPORT friend QDebug operator<<(QDebug dbg, const QOrganizerItemFilter& filter);
#endif
    QSharedDataPointer<QOrganizerItemFilterPrivate> d_ptr;
};

const Q_ORGANIZER_EXPORT QOrganizerItemFilter operator&(const QOrganizerItemFilter& left, const QOrganizerItemFilter& right);
const Q_ORGANIZER_EXPORT QOrganizerItemFilter operator|(const QOrganizerItemFilter& left, const QOrganizerItemFilter& right);

QTORGANIZER_END_NAMESPACE

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO(QTORGANIZER_PREPEND_NAMESPACE(QOrganizerItemFilter), Q_MOVABLE_TYPE);
Q_DECLARE_OPERATORS_FOR_FLAGS(QTORGANIZER_PREPEND_NAMESPACE(QOrganizerItemFilter::MatchFlags))
QT_END_NAMESPACE

#endif
