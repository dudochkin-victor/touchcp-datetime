include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)
TARGET = ut_timeview

contains(DEFINES, HAVE_CELLULAR_QT) {
    message("Setting up CellularQt")
} else {
    message("CellularQt not installed")
    HEADERS += \
        $$SRCDIR/cellular-fake.h
    SOURCES += $$STUBSDIR/systemcontrol-fake.cpp
    SOURCES += $$STUBSDIR/sim-fake.cpp
}

contains(DEFINES, HAVE_QMSYSTEM) {
    message("Setting up QmSystem")
} else {
    message("QmSystem not installed")
    HEADERS += \
        $$SRCDIR/qmsystem-fake.h
    SOURCES += $$STUBSDIR/qmtime-fake.cpp
}


TEST_SOURCES = \
    $$SRCDIR/timeview.cpp \
    $$SRCDIR/translation.cpp \

# unit test and unit
SOURCES += \
    ut_timeview.cpp \
    $$STUBSDIR/mtheme-fake.cpp \
    $$STUBSDIR/mwidgetview-fake.cpp \
    $$STUBSDIR/mwidgetcontroller-fake.cpp \
    $$STUBSDIR/mapplication-fake.cpp \
    $$STUBSDIR/mapplicationpage-fake.cpp \
    $$STUBSDIR/mapplicationwindow-fake.cpp \
    $$STUBSDIR/mwindow-fake.cpp \
    $$STUBSDIR/mabstractlayoutpolicy-fake.cpp \
    $$STUBSDIR/mlinearlayoutpolicy-fake.cpp \
    $$STUBSDIR/mgridlayoutpolicy-fake.cpp \
    $$STUBSDIR/mlayout-fake.cpp \
    $$STUBSDIR/settings-fake.cpp \
    $$STUBSDIR/mgconfitem-fake.cpp \
    $$STUBSDIR/qgraphicslayoutitem-fake.cpp \
    $$STUBSDIR/datepicker-mock.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_timeview.h \
    $$SRCDIR/timeview.h \
    $$SRCDIR/settings.h \
    $$SRCDIR/translation.h \
    $$STUBSDIR/mwindow-fake.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


