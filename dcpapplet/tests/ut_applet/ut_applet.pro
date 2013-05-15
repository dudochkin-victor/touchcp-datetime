include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_applet

TEST_SOURCES = \
    $$SRCDIR/applet.cpp \
    $$SRCDIR/translation.cpp \

# unit test and unit
SOURCES += \
    ut_applet.cpp \
    $$STUBSDIR/mapplicationwindow-fake.cpp \
    $$STUBSDIR/mapplication-fake.cpp \
    $$STUBSDIR/mapplicationpage-fake.cpp \
    $$STUBSDIR/mwindow-fake.cpp \
    $$STUBSDIR/mtheme-fake.cpp \
    $$STUBSDIR/mwidgetcontroller-fake.cpp \
    $$STUBSDIR/dateview-fake.cpp \
    $$STUBSDIR/timeview-fake.cpp \
    $$STUBSDIR/timezoneview-fake.cpp \
    $$STUBSDIR/mainview-fake.cpp \
    $$STUBSDIR/brief-fake.cpp \
    $$STUBSDIR/datepicker-mock.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_applet.h \
    $$SRCDIR/applet.h \
    $$SRCDIR/dateview.h \
    $$SRCDIR/timeview.h \
    $$SRCDIR/timezoneview.h \
    $$SRCDIR/mainview.h \
    $$SRCDIR/brief.h \
    $$SRCDIR/translation.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


