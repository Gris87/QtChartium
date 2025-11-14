QT += widgets

CONFIG += c++20
CONFIG += staticlib

TARGET = qtchartium
TEMPLATE = lib



# Disable warnings - BEGIN
win32-msvc* {
    QMAKE_CXXFLAGS_WARN_ON -= -W3 -w34100 -w34189 -w44456 -w44457 -w44458 -wd4577 -wd4467
    QMAKE_CXXFLAGS_WARN_ON += /w
} else {
    QMAKE_CXXFLAGS_WARN_ON += -w
}
# Disable warnings - END

# Extend number of sections - BEGIN
win32-msvc* {
    QMAKE_CXXFLAGS += -bigobj
}
# Extend number of sections - END

# Target dirs - BEGIN
DESTDIR     = build/
OBJECTS_DIR = build/gen/$${TARGET}/objs
MOC_DIR     = build/gen/$${TARGET}/moc
RCC_DIR     = build/gen/$${TARGET}/rcc
UI_DIR      = build/gen/$${TARGET}/ui
# Target dirs - END



# find libs/qtchartium/ -name \*.cpp | sort | sed "s/libs\/qtchartium\///g" | sed "s/\.cpp/\.cpp \\\/g"
SOURCES += \
    src/qtchartium/chartiumaxis.cpp \
    src/qtchartium/chartiumchart.cpp \
    src/qtchartium/chartiumlegend.cpp \
    src/qtchartium/chartiumlineseries.cpp \
    src/qtchartium/chartiumseries.cpp \
    src/qtchartium/chartiumview.cpp \

# find libs/qtchartium/ -name \*.h | sort | sed "s/libs\/qtchartium\///g" | sed "s/\.h/\.h \\\/g"
HEADERS += \
    src/qtchartium/chartiumaxis.h \
    src/qtchartium/chartiumchart.h \
    src/qtchartium/chartiumlegend.h \
    src/qtchartium/chartiumlineseries.h \
    src/qtchartium/chartiumseries.h \
    src/qtchartium/chartiumview.h \
    src/qtchartium/ichartiumaxis.h \
    src/qtchartium/ichartiumchart.h \
    src/qtchartium/ichartiumlegend.h \
    src/qtchartium/ichartiumlineseries.h \
    src/qtchartium/ichartiumseries.h \
    src/qtchartium/ichartiumview.h \
