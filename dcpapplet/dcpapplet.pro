TEMPLATE = subdirs

CONFIG = build_all warn_on
CONFIG += conf

SUBDIRS += src translations tests

include(common.pri)
include(desktop/desktop.pri)
include(share/share.pri)
check.commands = cd test ; qmake ; make check ;  cd ..                                                                                                                       
QMAKE_EXTRA_TARGETS += check

contains(DCP_BUILD_FEATURES,coverage) {
  QMAKE_EXTRA_TARGETS += coverage
  coverage.target = coverage
  coverage.CONFIG = recursive
}
