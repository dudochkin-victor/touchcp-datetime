TEMPLATE    = subdirs

# this is only necessery because subprojects uses one compilation directory
CONFIG += ordered

SUBDIRS = ut_applet \
	ut_autosyncbutton \
	ut_brief \
	ut_dateview \
	ut_mainview \
	ut_timeview \
	ut_timezonemodel \
	qmsystem \

load(qmsystem) {
    SUBDIRS += ut_settings
}
include(shell.pri)
QMAKE_STRIP = echo

check.target = check
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check


check-xml.target = check-xml
check-xml.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check-xml

contains(DCP_BUILD_FEATURES,coverage) {
  QMAKE_EXTRA_TARGETS += coverage
  coverage.target = coverage
  coverage.CONFIG = recursive
}


QMAKE_CLEAN += **/*.log.xml **/*.log
