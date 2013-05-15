
include(common.pri)

LOGDEBUG=$$(LOGDEBUG)
contains(LOGDEBUG, yes){
	CONFIG += debug
    message("debug is on")
}

RUNTIMEBACKTRACE=$$(RUNTIMEBACKTRACE)
contains(RUNTIMEBACKTRACE, yes){
	DEFINES += RUNTIME_BACKTRACE
	QMAKE_CXXFLAGS += -finstrument-functions
	QMAKE_LFLAGS += -rdynamic
}

debug{
        DEFINES += DEBUG
} else {
	DEFINES += QT_NO_DEBUG_OUTPUT
	CONFIG += release
}

