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


#ifndef QORGANIZERRECURRENCERULE_H
#define QORGANIZERRECURRENCERULE_H

#include <qorganizerglobal.h>

#include <QString>
#include <QDateTime>
#include <QSet>
#include <QHash>
#ifndef QT_NO_DEBUG_STREAM
#include <QtCore/qdebug.h>
#endif

QTORGANIZER_BEGIN_NAMESPACE
class QOrganizerRecurrenceRulePrivate;

class Q_ORGANIZER_EXPORT QOrganizerRecurrenceRule
{
public:
    QOrganizerRecurrenceRule();
    ~QOrganizerRecurrenceRule();
    QOrganizerRecurrenceRule(const QOrganizerRecurrenceRule& other);
    QOrganizerRecurrenceRule& operator=(const QOrganizerRecurrenceRule& other);
    bool operator==(const QOrganizerRecurrenceRule& other) const;
    // enums
    enum Frequency {
        Invalid = 0,
        Daily,
        Weekly,
        Monthly,
        Yearly
    };

    enum Month {
        January = 1,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December
    };

    enum LimitType {
        NoLimit = 0,
        CountLimit,
        DateLimit
    };

    void setFrequency(Frequency freq);
    Frequency frequency() const;

    void setLimit(int count);
    void setLimit(const QDate& date);
    void clearLimit();

    LimitType limitType() const;
    int limitCount() const;
    QDate limitDate() const;

    void setInterval(int interval);
    int interval() const; // units of frequency

    // Defaults for the below: empty
    // eg: Monday,Wednesday,Thursday == every Mon, Wed and Thurs.
    void setDaysOfWeek(const QSet<Qt::DayOfWeek>& days);
    QSet<Qt::DayOfWeek> daysOfWeek() const;
    // eg: 31,-3 == 31st day of month (if it exists) and 3rd-last day of month
    void setDaysOfMonth(const QSet<int>& days);
    QSet<int> daysOfMonth() const;
    // eg: 47th,-5 == 47th and 5th-last day of year
    void setDaysOfYear(const QSet<int>& days);
    QSet<int> daysOfYear() const;
    // eg: January,February == during Jan and Feb
    void setMonthsOfYear(const QSet<Month>& months);
    QSet<Month> monthsOfYear() const;
    // eg. 13,53,-3 == weeks 13 and 53 (if it exists) and the 3rd-last week of the year
    void setWeeksOfYear(const QSet<int>& weeks);
    QSet<int> weeksOfYear() const;

    // Default: Monday
    // sets the day that the week starts on (significant for Weekly with interval > 1, and for weekOfYear)
    void setFirstDayOfWeek(Qt::DayOfWeek day);
    Qt::DayOfWeek firstDayOfWeek() const;

    // eg. frequency = Monthly, dayOfWeek = Tuesday, positions = 1,-1 means first and last Tuesday
    // of every month.
    // All other criteria are applied first, then for each time period as specified by frequency,
    // dates are selected via the 1-based indices specified by position.
    void setPositions(const QSet<int>& pos);
    QSet<int> positions() const;

private:
    QSharedDataPointer<QOrganizerRecurrenceRulePrivate> d;
};

//hash functions
Q_ORGANIZER_EXPORT uint qHash(const QOrganizerRecurrenceRule& rule);

#ifndef QT_NO_DEBUG_STREAM
Q_ORGANIZER_EXPORT QDebug operator<<(QDebug dbg, const QOrganizerRecurrenceRule& rule);
#endif

inline uint qHash(QOrganizerRecurrenceRule::Month month)
{
    return static_cast<uint>(month);
}

QTORGANIZER_END_NAMESPACE

QT_BEGIN_NAMESPACE
inline uint qHash(const QDate &date)
{
    return date.toJulianDay();
}

Q_DECLARE_TYPEINFO(QTORGANIZER_PREPEND_NAMESPACE(QOrganizerRecurrenceRule), Q_MOVABLE_TYPE);
QT_END_NAMESPACE

Q_DECLARE_METATYPE(QTORGANIZER_PREPEND_NAMESPACE(QOrganizerRecurrenceRule));
Q_DECLARE_METATYPE(QSet<QTORGANIZER_PREPEND_NAMESPACE(QOrganizerRecurrenceRule)>);
Q_DECLARE_METATYPE(QSet<QDate>);

#endif
