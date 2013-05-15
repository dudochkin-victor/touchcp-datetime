
include ($$[QT_INSTALL_DATA]/mkspecs/dcpconfig.pri)

#
#	remove everything we want to set by ourselves
#
#CONFIG -= lex yacc uic resources incremental link_prl nostrip exceptions no_mocdepend stl qt_no_framework qt warn_on release debug build_all silent thread
#QMAKE_CXXFLAGS = ""
#QMAKE_CXXFLAGS_DEBUG = ""
#QMAKE_CXXFLAGS_RELEASE = ""
#QMAKE_CXXFLAGS_SHLIB = ""

exists(/usr/include/timepicker/timepicker.h) {
    message("TimePicker installed")
    DEFINES += HAVE_TIMEPICKER
}

exists(/usr/share/meegotouch/locationdatabase/cities.xml) {
    message("Cities data installed")
    DEFINES += HAVE_CITIES
}


load(cellular-qt) {
    message("CellularQt installed")
    DEFINES += HAVE_CELLULAR_QT
}
load(datepicker2) {
    message("DatePicker installed")
    DEFINES += HAVE_DATEPICKER
}
load(qmsystem2) {
    message("QmSystem2 installed")
    DEFINES += HAVE_QMSYSTEM
}

#
#	Start to configure
#

QMAKE_CXXFLAGS_DEBUG += -O0
QMAKE_CXXFLAGS_RELEASE += -O2
QMAKE_CXXFLAGS += -g -Werror

CONFIG += qt no_mocdepend
CONFIG += gui meegotouch duicontrolpanel
CONFIG += build_all warn_on
CONFIG += nostrip
CONFIG += stl
CONFIG += ordered
#CONFIG += silent

PREFIX = $$DCP_PREFIX

# try to detect maemo environment 

MAEMOTARGET = $$system(cpp -dM /dev/null | grep ARM)
!isEmpty(MAEMOTARGET){
        CONFIG += maemo
}
maemo{
        DEFINES += MAEMO
}

OBJECTS_DIR = .obj
MOC_DIR = .moc

QMAKE_CLEAN += .obj/* .moc/*

#
# some debugging related config both for tests and product
#
QMAKE_CXXFLAGS += -finstrument-functions-exclude-file-list=/bits/stl,include/sys,debug,qt,meego,qmsystem2,string,unistd,include/unicode
QMAKE_CXXFLAGS += -finstrument-functions-exclude-function-list=new,metaObject,qt_metacall

