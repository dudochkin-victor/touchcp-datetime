
!silent{
	message(------$(PWD)------)
	message(DESTDIR:		$$DESTDIR)
	message(PREFIX:			$$PREFIX)
	message(DCP_PREFIX:		$$DCP_PREFIX)

	message(target.path:		$$target.path)
	message(css.path:		$$css.path)

	message(INCLUDEPATH:		$$INCLUDEPATH)
	message(QMAKE_INCDIR:		$$QMAKE_INCDIR)
	message(QMAKE_INCDIR_QT:	$$QMAKE_INCDIR_QT)

	message(QMAKE_CXXFLAGS:		$$QMAKE_CXXFLAGS)
	message(QMAKE_CXXFLAGS_DEBUG:	$$QMAKE_CXXFLAGS_DEBUG)
	message(QMAKE_CXXFLAGS_RELEASE:	$$QMAKE_CXXFLAGS_RELEASE)
	message(QMAKE_CXXFLAGS_SHLIB:	$$QMAKE_CXXFLAGS_SHLIB)
	message(QMAKE_LFLAGS:		$$QMAKE_LFLAGS)

	message(QMAKE_LIBDIR:		$$QMAKE_LIBDIR)

	message(DEFINES:		$$DEFINES)

	message(CONFIG:			$$CONFIG)
	message(QT:			$$QT)

	message(DCP_THEME_DIR:		$$DCP_THEME_DIR)
	message(DCP_APPLET_DIR:		$$DCP_APPLET_DIR)
	message(DCP_DESKTOP_DIR:	$$DCP_DESKTOP_DIR)
	message(UT_INSTALL_DIR:		$$UT_INSTALL_DIR)
	message(------------------)
}

