TEMPLATE = subdirs
SUBDIRS += dcpapplet 

check.commands = cd dcpapplet; make check; cd ..
QMAKE_EXTRA_TARGETS += check
contains(DCP_BUILD_FEATURES,coverage) {
QMAKE_EXTRA_TARGETS += coverage
coverage.depends = dcpapplet/src/Makefile
coverage.commands = cd dcpapplet && make coverage && cd .. \
                      && genhtml --no-branch-coverage --legend \ 
                            -t \"dcp datetime applet unit test coverage\" \
                            -o coverage/ dcpapplet/tests/ut*/selected.cov
QMAKE_DISTCLEAN += -r coverage/*
}
