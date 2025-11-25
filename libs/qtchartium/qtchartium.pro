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
    src/qtchartium/axis/barcategoryaxis/chartiumbarcategoryaxis.cpp \
    src/qtchartium/axis/chartiumaxis.cpp \
    src/qtchartium/axis/chartiumaxiselement.cpp \
    src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxis.cpp \
    src/qtchartium/axis/valueaxis/chartiumvalueaxis.cpp \
    src/qtchartium/chartiumbackground.cpp \
    src/qtchartium/chartiumchart.cpp \
    src/qtchartium/chartiumdataset.cpp \
    src/qtchartium/chartiumelement.cpp \
    src/qtchartium/chartiumitem.cpp \
    src/qtchartium/chartiumpresenter.cpp \
    src/qtchartium/chartiumseries.cpp \
    src/qtchartium/chartiumtitle.cpp \
    src/qtchartium/chartiumview.cpp \
    src/qtchartium/domain/chartiumdomain.cpp \
    src/qtchartium/domain/chartiumxydomain.cpp \
    src/qtchartium/layout/chartiumcartesianlayout.cpp \
    src/qtchartium/layout/chartiumlayout.cpp \
    src/qtchartium/legend/chartiumlegend.cpp \
    src/qtchartium/legend/chartiumlegendmarker.cpp \
    src/qtchartium/legend/chartiumlegendscroller.cpp \
    src/qtchartium/linechart/chartiumlineseries.cpp \

# find libs/qtchartium/ -name \*.h | sort | sed "s/libs\/qtchartium\///g" | sed "s/\.h/\.h \\\/g"
HEADERS += \
    src/qtchartium/axis/barcategoryaxis/chartiumbarcategoryaxis.h \
    src/qtchartium/axis/barcategoryaxis/ichartiumbarcategoryaxis.h \
    src/qtchartium/axis/chartiumaxis.h \
    src/qtchartium/axis/chartiumaxiselement.h \
    src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxis.h \
    src/qtchartium/axis/datetimeaxis/ichartiumdatetimeaxis.h \
    src/qtchartium/axis/ichartiumaxis.h \
    src/qtchartium/axis/ichartiumaxiselement.h \
    src/qtchartium/axis/valueaxis/chartiumvalueaxis.h \
    src/qtchartium/axis/valueaxis/ichartiumvalueaxis.h \
    src/qtchartium/chartiumbackground.h \
    src/qtchartium/chartiumchart.h \
    src/qtchartium/chartiumdataset.h \
    src/qtchartium/chartiumelement.h \
    src/qtchartium/chartiumitem.h \
    src/qtchartium/chartiumpresenter.h \
    src/qtchartium/chartiumseries.h \
    src/qtchartium/chartiumtitle.h \
    src/qtchartium/chartiumview.h \
    src/qtchartium/domain/chartiumdomain.h \
    src/qtchartium/domain/chartiumxydomain.h \
    src/qtchartium/domain/ichartiumdomain.h \
    src/qtchartium/domain/ichartiumxydomain.h \
    src/qtchartium/ichartiumbackground.h \
    src/qtchartium/ichartiumchart.h \
    src/qtchartium/ichartiumdataset.h \
    src/qtchartium/ichartiumelement.h \
    src/qtchartium/ichartiumitem.h \
    src/qtchartium/ichartiumpresenter.h \
    src/qtchartium/ichartiumseries.h \
    src/qtchartium/ichartiumtitle.h \
    src/qtchartium/ichartiumview.h \
    src/qtchartium/layout/chartiumcartesianlayout.h \
    src/qtchartium/layout/chartiumlayout.h \
    src/qtchartium/layout/ichartiumcartesianlayout.h \
    src/qtchartium/layout/ichartiumlayout.h \
    src/qtchartium/legend/chartiumlegend.h \
    src/qtchartium/legend/chartiumlegendmarker.h \
    src/qtchartium/legend/chartiumlegendscroller.h \
    src/qtchartium/legend/ichartiumlegend.h \
    src/qtchartium/legend/ichartiumlegendmarker.h \
    src/qtchartium/legend/ichartiumlegendscroller.h \
    src/qtchartium/linechart/chartiumlineseries.h \
    src/qtchartium/linechart/ichartiumlineseries.h \
