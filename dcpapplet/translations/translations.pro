LANGUAGES = # empty, means to build only engineering English
CATALOGNAME = date-time
SOURCEDIR = $$PWD/../src
TRANSLATIONDIR = $$PWD
TRANSLATION_INSTALLDIR = /usr/share/l10n/meegotouch
include(../translations.pri)
contains(DCP_BUILD_FEATURES,coverage) {
  QMAKE_EXTRA_TARGETS += coverage
  coverage.commands = $$system(true)
}
