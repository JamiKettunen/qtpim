/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtVersit module of the Qt Toolkit.
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

#include "qversitdocumentwriter_p.h"

#include <QtCore/qiodevice.h>
#include <QtCore/qbytearray.h>

#include <QTextCodec>

#include "qversitutils_p.h"

QT_BEGIN_NAMESPACE_VERSIT

#define MAX_LINE_LENGTH 76

/*!
  \class QVersitDocumentWriter
  \internal
  \brief The QVersitDocumentWriter class provides an interface for writing a
  single versit document into a vCard text string.
 */

/*! Constructs a writer.
 * \a documentType is the type of Versit document, as printed on the BEGIN line of output
 * eg. "VCARD"
 * \a version is the version of the Versit format, as printed on the VERSION line of output.
 * eg. "2.1"
 */
QVersitDocumentWriter::QVersitDocumentWriter(QVersitDocument::VersitType type)
    : mType(type),
    mDevice(0),
    mCodec(0),
    mCodecIsAscii(false),
    mEncoder(0),
    mSuccessful(true),
    mCurrentLineLength(0)
{
}

QVersitDocumentWriter::~QVersitDocumentWriter()
{
    if (mEncoder)
        delete mEncoder;
}

/*!
  Sets the codec to write with.
  */
void QVersitDocumentWriter::setCodec(QTextCodec *codec)
{
    if (mEncoder)
        delete mEncoder;
    mCodec = codec;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    mEncoder = codec->makeEncoder();
    if (mCodec->name() == "UTF-8")
        mEncoder->fromUnicode(QString()); // Throw away BOM.
#else
    mEncoder = codec->makeEncoder(mCodec->name() == QByteArrayLiteral("UTF-8")
                ? QStringConverterBase::Flag::Default
                : QStringConverterBase::Flag::WriteBom);
#endif

    // UTF-(16|32)(LE|BE) are the only codecs where characters in the base64 range aren't encoded
    // the same as in ASCII.  For ASCII compatible codecs, we can do some optimizations.
    mCodecIsAsciiCompatible = !(mCodec->name().startsWith("UTF-16")
                             || mCodec->name().startsWith("UTF-32"));
}

/*!
  Specifies that the codec is actually ASCII (setCodec must also be called with an ASCII-compatible
  codec.
 */
void QVersitDocumentWriter::setAsciiCodec()
{
    mCodecIsAscii = true;
}

/*!
  Sets the device to write to.
  */
void QVersitDocumentWriter::setDevice(QIODevice *device)
{
    mDevice = device;
}

/*!
 * Encodes the \a document and writes it to the device.  A "VERSION:" line is added iff \a
 * encodeVersion is true.
 */
bool QVersitDocumentWriter::encodeVersitDocument(const QVersitDocument& document, bool encodeVersion)
{
    mSuccessful = true;

    if (document.componentType().isEmpty()) {
        // for compatibility with code for Qt Mobility 1.0, which didn't have componentType
        writeString(QStringLiteral("BEGIN:VCARD"));
    } else {
        writeString(QStringLiteral("BEGIN:") + document.componentType());
    }
    writeCrlf();
    if (encodeVersion) {
        switch (mType) {
        case QVersitDocument::VCard21Type:
            writeString(QStringLiteral("VERSION:2.1"));
            writeCrlf();
            break;
        case QVersitDocument::VCard30Type:
            writeString(QStringLiteral("VERSION:3.0"));
            writeCrlf();
            break;
        case QVersitDocument::VCard40Type:
            writeString(QStringLiteral("VERSION:4.0"));
            writeCrlf();
            break;
        case QVersitDocument::ICalendar20Type:
            writeString(QStringLiteral("VERSION:2.0"));
            writeCrlf();
            break;
        default:
            ; // don't print version
        }
    }

    foreach (const QVersitProperty& property, document.properties()) {
        encodeVersitProperty(property);
    }

    foreach (const QVersitDocument& document, document.subDocuments()) {
        encodeVersitDocument(document, false);
    }

    if (document.componentType().isEmpty()) {
        writeString(QStringLiteral("END:VCARD"));
    } else {
        writeString(QStringLiteral("END:") + document.componentType());
    }
    writeCrlf();

    // This has been set by the methods called from this function
    return mSuccessful;
}

/*!
 * Encodes the groups and name in the \a property and writes it to the device
 */
void QVersitDocumentWriter::encodeGroupsAndName(const QVersitProperty& property)
{
    QStringList groups = property.groups();
    if (!groups.isEmpty()) {
        writeString(groups.join(QStringLiteral(".")));
        writeString(QStringLiteral("."));
    }
    writeString(property.name());
}

/*!
  Writes \a value to the device.

  This function tracks how many characters have been written to the line and folds (wraps) the line
  according to RFC2425.
  */
void QVersitDocumentWriter::writeBytes(const QByteArray &value)
{
    int spaceRemaining = MAX_LINE_LENGTH - mCurrentLineLength;
    int charsWritten = 0;
    while (spaceRemaining < value.length() - charsWritten) {
        // Write the first "spaceRemaining" characters
        if (mDevice->write(value.constData() + charsWritten, spaceRemaining) < 0
               || mDevice->write("\r\n ") < 0)
            mSuccessful = false;
        charsWritten += spaceRemaining;
        spaceRemaining = MAX_LINE_LENGTH - 1; // minus 1 for the space at the front.
        mCurrentLineLength = 1;
    }

    if (mDevice->write(value.constData() + charsWritten) < 0)
        mSuccessful = false;
    mCurrentLineLength += value.length() - charsWritten;
}

/*!
  Writes \a value to the device.

  This function tracks how many characters have been written to the line and folds (wraps) the line
  according to RFC2425.
  */
void QVersitDocumentWriter::writeString(const QString &value)
{
    int spaceRemaining = MAX_LINE_LENGTH - mCurrentLineLength;
    int charsWritten = 0;
    QString crlfSpace(QStringLiteral("\r\n "));
    while (spaceRemaining < value.length() - charsWritten) {
        // Write the first "spaceRemaining" characters
        QStringView line(value.constData() + charsWritten, spaceRemaining);
        charsWritten += spaceRemaining;
        const QByteArray encodedLine = mEncoder->fromUnicode(line.data(), line.length());
        const QByteArray encodedCrlfSpace = mEncoder->fromUnicode(crlfSpace);
        if (mDevice->write(encodedLine) < 0 || mDevice->write(encodedCrlfSpace) < 0)
            mSuccessful = false;
        spaceRemaining = MAX_LINE_LENGTH - 1; // minus 1 for the space at the front.
        mCurrentLineLength = 1;
    }

    const QByteArray encodedRemainder = mEncoder->fromUnicode(value.mid(charsWritten));
    if (mDevice->write(encodedRemainder) < 0)
        mSuccessful = false;
    mCurrentLineLength += value.length() - charsWritten;
}

/*!
  Writes \a value to the device.

  This function tracks how many characters have been written to the line and wraps the line
  according to RFC2045 (a Quoted-Printable soft line break is an EQUALS-CR-LF sequence)
  */
void QVersitDocumentWriter::writeStringQp(const QString &value)
{
    int spaceRemaining = MAX_LINE_LENGTH - mCurrentLineLength - 1;
                                             // minus 1 for the equals required at the end
    int charsWritten = 0;
    QString softBreak(QStringLiteral("=\r\n"));
    while (spaceRemaining < value.length() - charsWritten) {
        // Write the first "spaceRemaining" characters
        if (value[charsWritten + spaceRemaining - 2] == QLatin1Char('=')) {
            spaceRemaining -= 2;
        } else if (value[charsWritten + spaceRemaining - 1] == QLatin1Char('=')) {
            spaceRemaining -= 1;
        }
        QStringView line(value.constData() + charsWritten, spaceRemaining);

        charsWritten += spaceRemaining;
        if (mDevice->write(mEncoder->fromUnicode(line.data(), line.length())) < 0
               || mDevice->write(mEncoder->fromUnicode(softBreak)) < 0)
            mSuccessful = false;
        spaceRemaining = MAX_LINE_LENGTH - 1; // minus 1 for the equals required at the end
        mCurrentLineLength = 0;
    }

    if (mDevice->write(mEncoder->fromUnicode(value.mid(charsWritten))) < 0)
        mSuccessful = false;
    mCurrentLineLength += value.length() - charsWritten;
}

/*!
  Writes a CRLF to the device.  By using this function, rather than writeString("\\r\\n"), you will
  allow the writer to know where a line starts, for folding purposes.
  */
void QVersitDocumentWriter::writeCrlf()
{
    writeString(QStringLiteral("\r\n"));
    mCurrentLineLength = 0;
}

QT_END_NAMESPACE_VERSIT
