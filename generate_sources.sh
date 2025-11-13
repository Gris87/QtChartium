#!/bin/bash



PATH_TO_QT_CHARTIUM_PRO="libs/qtchartium/qtchartium.pro"



########################################################################################################################

echo "QT += widgets"                                                                                                       >> ${PATH_TO_QT_CHARTIUM_PRO}
echo ""                                                                                                                    >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "CONFIG += c++20"                                                                                                     >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "CONFIG += staticlib"                                                                                                 >> ${PATH_TO_QT_CHARTIUM_PRO}
echo ""                                                                                                                    >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "TARGET = qtchartium"                                                                                                 >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "TEMPLATE = lib"                                                                                                      >> ${PATH_TO_QT_CHARTIUM_PRO}
echo ""                                                                                                                    >> ${PATH_TO_QT_CHARTIUM_PRO}
echo ""                                                                                                                    >> ${PATH_TO_QT_CHARTIUM_PRO}
echo ""                                                                                                                    >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "# Disable warnings - BEGIN"                                                                                          >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "win32-msvc* {"                                                                                                       >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "    QMAKE_CXXFLAGS_WARN_ON -= -W3 -w34100 -w34189 -w44456 -w44457 -w44458 -wd4577 -wd4467"                           >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "    QMAKE_CXXFLAGS_WARN_ON += /w"                                                                                    >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "} else {"                                                                                                            >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "    QMAKE_CXXFLAGS_WARN_ON += -w"                                                                                    >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "}"                                                                                                                   >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "# Disable warnings - END"                                                                                            >> ${PATH_TO_QT_CHARTIUM_PRO}
echo ""                                                                                                                    >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "# Extend number of sections - BEGIN"                                                                                 >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "win32-msvc* {"                                                                                                       >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "    QMAKE_CXXFLAGS += -bigobj"                                                                                       >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "}"                                                                                                                   >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "# Extend number of sections - END"                                                                                   >> ${PATH_TO_QT_CHARTIUM_PRO}
echo ""                                                                                                                    >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "# Target dirs - BEGIN"                                                                                               >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "DESTDIR     = build/"                                                                                                >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "OBJECTS_DIR = build/gen/\$\${TARGET}/objs"                                                                           >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "MOC_DIR     = build/gen/\$\${TARGET}/moc"                                                                            >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "RCC_DIR     = build/gen/\$\${TARGET}/rcc"                                                                            >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "UI_DIR      = build/gen/\$\${TARGET}/ui"                                                                             >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "# Target dirs - END"                                                                                                 >> ${PATH_TO_QT_CHARTIUM_PRO}
echo ""                                                                                                                    >> ${PATH_TO_QT_CHARTIUM_PRO}
echo ""                                                                                                                    >> ${PATH_TO_QT_CHARTIUM_PRO}
echo ""                                                                                                                    >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "# find libs/qtchartium/ -name \\*.cpp | sort | sed \"s/libs\\/qtchartium\\///g\" | sed \"s/\\.cpp/\\.cpp \\\\\\/g\"" >> ${PATH_TO_QT_CHARTIUM_PRO}

echo "SOURCES += \\" >> ${PATH_TO_QT_CHARTIUM_PRO}
find libs/qtchartium/ -name \*.cpp | sort | sed "s/libs\/qtchartium\//    /g" | sed "s/\.cpp/\.cpp \\\/g" >> ${PATH_TO_QT_CHARTIUM_PRO}

echo "" >> ${PATH_TO_QT_CHARTIUM_PRO}
echo "# find libs/qtchartium/ -name \\*.h | sort | sed \"s/libs\\/qtchartium\\///g\" | sed \"s/\\.h/\\.h \\\\\\/g\"" >> ${PATH_TO_QT_CHARTIUM_PRO}

echo "HEADERS += \\" >> ${PATH_TO_QT_CHARTIUM_PRO}
find libs/qtchartium/ -name \*.h | sort | sed "s/libs\/qtchartium\//    /g" | sed "s/\.h/\.h \\\/g" >> ${PATH_TO_QT_CHARTIUM_PRO}
