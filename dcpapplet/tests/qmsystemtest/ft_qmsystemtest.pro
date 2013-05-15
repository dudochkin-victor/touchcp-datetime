include(../ut-head.pri)

CONFIG += duicontrolpanel

TEST_SOURCES = \
#	$$PKGROOT/src/displaylangapplet.cpp

HEADERS += *.h \
#	$$PKGROOT/src/displaylangapplet.h \

SOURCES += *.cpp \
	$$TEST_SOURCES

TARGET = ft_displaylangapplet

include(../ut-tail.pri)

