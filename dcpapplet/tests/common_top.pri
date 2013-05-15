include($$[QT_INSTALL_DATA]/mkspecs/dcpconfig.pri)
include(../common.pri)

STUBSDIR += ../doubles
INCLUDEPATH += $$STUBSDIR

SRCDIR = ../../src

DEPENDPATH = $$INCLUDEPATH

QMAKE_LIBDIR += /usr/lib/

CONFIG += debug meegotouch duicontrolpanel
CONFIG += plugin

QT += testlib

TEMPLATE = app

contains(DEFINES, HAVE_DATEPICKER) {
    message("Setting up DatePicker")
} else {
    message("Datepicker not installed")
    HEADERS += \
        $$SRCDIR/datepicker-fake.h
}

contains(DEFINES, HAVE_TIMEPICKER) {
    message("Setting up TimePicker")
    CONFIG += timepicker
    timepicker{
        LIBS += -ltimepicker
        INCLUDEPATH += /usr/include/timepicker
    }
} else {
    message("TimePicker not installed")
    HEADERS += \
        $$SRCDIR/timepicker-fake.h
    SOURCES += \
        $$SRCDIR/timepicker-fake.cpp
}
DEFINES += QT_NO_DEBUG_OUTPUT
#DEFINES += QT_NO_WARNING_OUTPUT
DEFINES += UNIT_TEST

# disable internal deprecation warnings:
DEFINES += DCP_DISABLE_DEPRECATION_WARNING


DCP_TESTS_INSTALL_LIB = $${DCP_INSTALL_LIB}/duicontrolpanel-datetimeapplet-tests
target.path = $${DCP_TESTS_INSTALL_LIB}
INSTALLS += target
include(check.pri)
include(coverage.pri)
LIBS += -L/usr/lib -lduicontrolpanel
QMAKE_CXXFLAGS += -Werror
message($$target.path)

contains(DCP_BUILD_FEATURES,coverage) {

    OBJECTS_DIR=.tmp
    MOC_DIR=.tmp
}
else {
    OBJECTS_DIR=../.tmp
    MOC_DIR=../.tmp
}

