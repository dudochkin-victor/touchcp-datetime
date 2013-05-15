include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_timezonemodel

TEST_SOURCES = \
    $$SRCDIR/timezonemodel.cpp \

# unit test and unit
SOURCES += \
    ut_timezonemodel.cpp \
    $$STUBSDIR/datepicker-mock.cpp \
#ifndef HAVE_CITIES
    $$SRCDIR/mlocationdatabase-fake.cpp \
#endif
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_timezonemodel.h \
    $$SRCDIR/timezonemodel.h \
#ifndef HAVE_CITIES
    $$SRCDIR/mlocationdatabase-fake.h \
#endif

# base classes
HEADERS += \


# service classes
HEADERS += \


