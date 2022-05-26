include(../../auto.pri)

QT += versit versit-private
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

HEADERS += tst_qvcard21writer.h
SOURCES += tst_qvcard21writer.cpp

CONFIG+=insignificant_test # QTBUG-25382
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
