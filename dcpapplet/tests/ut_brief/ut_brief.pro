include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_brief

contains(DEFINES, HAVE_QMSYSTEM) {
    message("Setting up QmSystem")
} else {
    message("QmSystem not installed")
    HEADERS += \
        $$SRCDIR/qmsystem-fake.h
    SOURCES += $$STUBSDIR/qmtime-fake.cpp
}

contains(DEFINES, HAVE_CELLULAR_QT) {
    message("Setting up CellularQt")
} else {
    message("CellularQt not installed")
    HEADERS += \
        $$SRCDIR/cellular-fake.h
    SOURCES += $$STUBSDIR/systemcontrol-fake.cpp \
                $$STUBSDIR/sim-fake.cpp
}
TEST_SOURCES = \
    $$SRCDIR/brief.cpp \

# unit test and unit
SOURCES += \
    ut_brief.cpp \
    $$SRCDIR/translation.cpp \
    $$STUBSDIR/settings-fake.cpp \
    $$STUBSDIR/datepicker-mock.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_brief.h \
    $$SRCDIR/brief.h \
    $$SRCDIR/settings.h \
    $$SRCDIR/translation.h \


# base classes
HEADERS += \


# service classes
HEADERS += \


