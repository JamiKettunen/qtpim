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

#ifndef QCONTACTCHANGELOGFILTER_P_H
#define QCONTACTCHANGELOGFILTER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtContacts/qcontactchangelogfilter.h>
#include <QtContacts/private/qcontactfilter_p.h>

QT_BEGIN_NAMESPACE_CONTACTS

class QContactChangeLogFilterPrivate : public QContactFilterPrivate
{
public:
    QContactChangeLogFilterPrivate(QContactChangeLogFilter::EventType type = QContactChangeLogFilter::EventAdded)
        : QContactFilterPrivate()
        , m_eventType(type)
    {

    }

    QContactChangeLogFilterPrivate(const QContactChangeLogFilterPrivate& other)
        : QContactFilterPrivate(other)
        , m_eventType(other.m_eventType)
        , m_since(other.m_since)
    {

    }

    bool compare(const QContactFilterPrivate* other) const override
    {
        const QContactChangeLogFilterPrivate *od = static_cast<const QContactChangeLogFilterPrivate*>(other);
        if (m_eventType != od->m_eventType)
            return false;
        if (m_since != od->m_since)
            return false;
        return true;
    }

    QDataStream& outputToStream(QDataStream& stream, quint8 formatVersion) const override
    {
        if (formatVersion == 1) {
            stream << static_cast<quint32>(m_eventType) << m_since;
        }
        return stream;
    }

    QDataStream& inputFromStream(QDataStream& stream, quint8 formatVersion) override
    {
        if (formatVersion == 1) {
            quint32 eventType;
            stream >> eventType >> m_since;
            m_eventType = (QContactChangeLogFilter::EventType)eventType;
        }
        return stream;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug& dbg) const override
    {
        dbg.nospace() << "QContactChangeLogFilter(";
        dbg.nospace() << "eventType=" << static_cast<quint32>(m_eventType) << ",since=" << m_since;
        dbg.nospace() << ")";
        return dbg.maybeSpace();
    }
#endif

    Q_IMPLEMENT_CONTACTFILTER_VIRTUALCTORS(QContactChangeLogFilter, QContactFilter::ChangeLogFilter)

    QContactChangeLogFilter::EventType m_eventType;
    QDateTime m_since;
};

QT_END_NAMESPACE_CONTACTS

#endif // QCONTACTCHANGELOGFILTER_P_H
