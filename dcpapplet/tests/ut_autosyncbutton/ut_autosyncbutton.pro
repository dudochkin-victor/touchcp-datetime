include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_autosyncbutton

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
    $$SRCDIR/autosyncbutton.cpp \
    $$SRCDIR/translation.cpp \

# unit test and unit
SOURCES += \
    $$STUBSDIR/mtheme-fake.cpp \
    ut_autosyncbutton.cpp \
    $$STUBSDIR/mapplication-fake.cpp \
    $$STUBSDIR/mapplicationpage-fake.cpp \
    $$STUBSDIR/mapplicationwindow-fake.cpp \
    $$STUBSDIR/mwindow-fake.cpp \
    $$STUBSDIR/mabstractlayoutpolicy-fake.cpp \
    $$STUBSDIR/mlinearlayoutpolicy-fake.cpp \
    $$STUBSDIR/mlayout-fake.cpp \
    $$STUBSDIR/settings-fake.cpp \
    $$STUBSDIR/mstylablewidget-fake.cpp \
    $$STUBSDIR/mbanner-fake.cpp \
    $$STUBSDIR/mgconfitem-fake.cpp \
    $$STUBSDIR/qpixmap-fake.cpp \
    $$STUBSDIR/qgraphicslayoutitem-fake.cpp \
    $$STUBSDIR/qgraphicslinearlayout-fake.cpp \
    $$STUBSDIR/mwidgetcontroller-fake.cpp \
    $$STUBSDIR/datepicker-mock.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_autosyncbutton.h \
    $$SRCDIR/autosyncbutton.h \
    $$SRCDIR/settings.h \
    $$SRCDIR/translation.h \
    $$STUBSDIR/mwindow-fake.h \

# base classes
HEADERS += \


# service classes
HEADERS += \

message(defnes  $$DEFINES)

