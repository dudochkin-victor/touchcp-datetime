include ($$[QT_INSTALL_DATA]/mkspecs/dcpconfig.pri)
date.files += setdate
date.commands += /bin/chmod a+x setdate
date.path = $$PREFIX/lib/duicontrolpanel/applets 
message("Using setdate "$$date.path)

INSTALLS += date
