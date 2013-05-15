TEMPLATE = lib

include(../product.pri)

CONFIG += plugin


QT = core gui

message($$(SBOX_DPKG_INST_ARCH))
ARCH = $$(SBOX_DPKG_INST_ARCH)

contains(ARCH,"i386"){
	DEFINES += SBOX
    message("sbox-i386")
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
        timepicker-fake.h
    SOURCES += \
        timepicker-fake.cpp
}

DEFINES += APP_NAME=\\\"\"datetime-app\"\\\"

target.path += $$DCP_APPLET_DIR

css.path += $$PREFIX/share/themes/base/meegotouch/libdatetimeapplet/style/
css.files = libdatetimeapplet.css
INSTALLS += css

conf.path += $$PREFIX/share/duicontrolpanel-datetimeapplet
conf.files = dcpdatetimeapplet.conf
INSTALLS += conf

#include(../report.pri)

contains(DEFINES, HAVE_CELLULAR_QT) {
    message("Setting up CellularQt")
} else {
    message("CellularQt not installed")
    HEADERS += \
        cellular-fake.h
    SOURCES += \
        cellular-fake.cpp
}

contains(DEFINES, HAVE_QMSYSTEM) {
    message("Setting up QmSystem")
} else {
    message("QmSystem not installed")
    include(system.pri)
    include(sudoers.pri)
    HEADERS += \
        qmsystem-fake.h
    SOURCES += \
        qmsystem-fake.cpp

}

contains(DEFINES, HAVE_DATEPICKER) {
    message("Setting up DatePicker")
} else {
    message("Datepicker not installed")
    HEADERS += \
        datepicker-fake.h
    SOURCES += \
        datepicker-fake.cpp
}

contains(DEFINES, HAVE_CITIES) {
    message("Usimg meegotouch-cities-default")
} else {
    message("Cities data not installed")
    HEADERS += \
        mlocationdatabase-fake.h 
    
    SOURCES += \
        mlocationdatabase-fake.cpp 
}

HEADERS += \
	debug.h \
	translation.h \
	timezonemodel.h \
	timezonecell.h \
	settings.h \
	autosyncbutton.h \
	viewid.h \
	dateview.h \
	timeview.h \
	timezoneview.h \
	mainview.h \
	brief.h \
	drilllistitem.h \
	titlewidget.h \
	applet.h

SOURCES += \
#	debug.cpp \
	translation.cpp \
	timezonemodel.cpp \
	settings.cpp \
	autosyncbutton.cpp \
	dateview.cpp \
	timeview.cpp \
	timezoneview.cpp \
	mainview.cpp \
	brief.cpp \
	drilllistitem.cpp \
	applet.cpp

TARGET = datetimeapplet
INSTALLS += target
contains(DCP_BUILD_FEATURES,coverage) {
  QMAKE_EXTRA_TARGETS += coverage
  coverage.commands = $$system(true)
}
