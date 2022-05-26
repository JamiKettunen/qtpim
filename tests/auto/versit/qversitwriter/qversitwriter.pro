include(../../auto.pri)

QT += versit versit-private
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

HEADERS += tst_qversitwriter.h
SOURCES += tst_qversitwriter.cpp
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
