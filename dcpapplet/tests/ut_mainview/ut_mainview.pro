include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_mainview

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
    SOURCES += $$STUBSDIR/systemcontrol-fake.cpp
    SOURCES += $$STUBSDIR/sim-fake.cpp
}

TEST_SOURCES = \
    $$SRCDIR/mainview.cpp \
    $$SRCDIR/translation.cpp \
    $$SRCDIR/timezonemodel.cpp \
#ifndef HAVE_CITIES
    $$SRCDIR/mlocationdatabase-fake.cpp \
#endif

# unit test and unit
SOURCES += \
    ut_mainview.cpp \
    $$SRCDIR/drilllistitem.cpp \
    $$STUBSDIR/mtheme-fake.cpp \
    $$STUBSDIR/mwidgetview-fake.cpp \
    $$STUBSDIR/mwidgetcontroller-fake.cpp \
    $$STUBSDIR/mapplication-fake.cpp \
    $$STUBSDIR/mapplicationpage-fake.cpp \
    $$STUBSDIR/mapplicationwindow-fake.cpp \
    $$STUBSDIR/mwindow-fake.cpp \
    $$STUBSDIR/autosyncbutton-fake.cpp \
    $$STUBSDIR/mabstractlayoutpolicy-fake.cpp \
    $$STUBSDIR/qgraphicslinearlayout-fake.cpp \
    $$STUBSDIR/qpixmap-fake.cpp \
    $$STUBSDIR/mbasiclistitem-fake.cpp \
    $$STUBSDIR/settings-fake.cpp \
    $$STUBSDIR/mgconfitem-fake.cpp \
    $$STUBSDIR/mlocale-fake.cpp \
    $$STUBSDIR/qgraphicslayoutitem-fake.cpp \
    $$STUBSDIR/datepicker-mock.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_mainview.h \
    $$SRCDIR/mainview.h \
    $$SRCDIR/settings.h \
    $$SRCDIR/autosyncbutton.h \
    $$SRCDIR/timezonemodel.h \
    $$SRCDIR/translation.h \
    $$SRCDIR/drilllistitem.h \
#ifndef HAVE_CITIES
    $$SRCDIR/mlocationdatabase-fake.h \
#endif

# base classes
HEADERS += \


# service classes
HEADERS += \


