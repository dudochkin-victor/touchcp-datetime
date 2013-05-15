include(../common.pri)
shell_scripts.commands += ./gen-tests-xml.sh > tests.xml
shell_scripts.files += tests.xml

shell_scripts.path += $$(DCP_PREFIX)/usr/share/duicontrolpanel-datetimeapplet-tests

shell_scripts.CONFIG += no_check_exist

INSTALLS    += shell_scripts

