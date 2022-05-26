include(../../auto.pri)

QT += versit versit-private
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

DEFINES += QT_ASCII_CAST_WARNINGS

HEADERS += tst_qvcard30writer.h
SOURCES += tst_qvcard30writer.cpp
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
