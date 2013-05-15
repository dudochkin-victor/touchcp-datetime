include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_settings

contains(DEFINES, HAVE_QMSYSTEM) {
    message("Setting up QmSystem")
} else {
    message("QmSystem not installed")
    HEADERS += \
        $$SRCDIR/qmsystem-fake.h
}

contains(DEFINES, HAVE_CELLULAR_QT) {
    message("Setting up CellularQt")
} else {
    message("CellularQt not installed")
    HEADERS += \
        $$SRCDIR/cellular-fake.h
}


TEST_SOURCES = \
    $$SRCDIR/settings.cpp \

# unit test and unit
SOURCES += \
    ut_settings.cpp \
    $$STUBSDIR/systemcontrol-fake.cpp \
    $$STUBSDIR/sim-fake.cpp \
    $$STUBSDIR/qmtime-fake.cpp \
    $$STUBSDIR/mgconfitem-fake.cpp \
    $$STUBSDIR/mlocale-fake.cpp \
    $$STUBSDIR/datepicker-mock.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_settings.h \
    $$SRCDIR/settings.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


