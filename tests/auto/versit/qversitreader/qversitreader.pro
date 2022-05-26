include(../../auto.pri)

QT += versit versit-private
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

HEADERS += tst_qversitreader.h
SOURCES += tst_qversitreader.cpp
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
