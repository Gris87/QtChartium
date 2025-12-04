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
    src/qtchartium/axis/barcategoryaxis/chartiumbarcategoryaxisx.cpp \
    src/qtchartium/axis/barcategoryaxis/chartiumbarcategoryaxisy.cpp \
    src/qtchartium/axis/chartiumaxis.cpp \
    src/qtchartium/axis/chartiumaxiselement.cpp \
    src/qtchartium/axis/chartiumcartesianaxis.cpp \
    src/qtchartium/axis/chartiumeditableaxislabel.cpp \
    src/qtchartium/axis/chartiumhorizontalaxis.cpp \
    src/qtchartium/axis/chartiumlinearrowitem.cpp \
    src/qtchartium/axis/chartiumverticalaxis.cpp \
    src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxis.cpp \
    src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxislabel.cpp \
    src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxisx.cpp \
    src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxisy.cpp \
    src/qtchartium/axis/valueaxis/chartiumvalueaxis.cpp \
    src/qtchartium/axis/valueaxis/chartiumvalueaxislabel.cpp \
    src/qtchartium/axis/valueaxis/chartiumvalueaxisx.cpp \
    src/qtchartium/axis/valueaxis/chartiumvalueaxisy.cpp \
    src/qtchartium/chartiumbackground.cpp \
    src/qtchartium/chartiumchart.cpp \
    src/qtchartium/chartiumdataset.cpp \
    src/qtchartium/chartiumelement.cpp \
    src/qtchartium/chartiumhelpers.cpp \
    src/qtchartium/chartiumitem.cpp \
    src/qtchartium/chartiumpresenter.cpp \
    src/qtchartium/chartiumtitle.cpp \
    src/qtchartium/chartiumview.cpp \
    src/qtchartium/charts/chartiumseries.cpp \
    src/qtchartium/charts/linechart/chartiumlinechartitem.cpp \
    src/qtchartium/charts/linechart/chartiumlineseries.cpp \
    src/qtchartium/charts/xychart/chartiumxychart.cpp \
    src/qtchartium/charts/xychart/chartiumxyseries.cpp \
    src/qtchartium/domain/chartiumdomain.cpp \
    src/qtchartium/domain/chartiumxydomain.cpp \
    src/qtchartium/layout/chartiumcartesianlayout.cpp \
    src/qtchartium/layout/chartiumlayout.cpp \
    src/qtchartium/legend/chartiumlegend.cpp \
    src/qtchartium/legend/chartiumlegendmarker.cpp \
    src/qtchartium/legend/chartiumlegendmarkerxy.cpp \
    src/qtchartium/legend/chartiumlegendscroller.cpp \
    src/qtchartium/legend/scroller/chartiumscroller.cpp \
    src/qtchartium/legend/scroller/chartiumscrollticker.cpp \
    src/qtchartium/themes/chartiumtheme.cpp \
    src/qtchartium/themes/chartiumthememanager.cpp \
    src/qtchartium/themes/custom/chartiumthemecustomdark.cpp \
    src/qtchartium/themes/qtcharts/chartiumthemebluecerulean.cpp \
    src/qtchartium/themes/qtcharts/chartiumthemeblueicy.cpp \
    src/qtchartium/themes/qtcharts/chartiumthemebluencs.cpp \
    src/qtchartium/themes/qtcharts/chartiumthemebrownsand.cpp \
    src/qtchartium/themes/qtcharts/chartiumthemedark.cpp \
    src/qtchartium/themes/qtcharts/chartiumthemehighcontrast.cpp \
    src/qtchartium/themes/qtcharts/chartiumthemelight.cpp \
    src/qtchartium/themes/qtcharts/chartiumthemeqt.cpp \

# find libs/qtchartium/ -name \*.h | sort | sed "s/libs\/qtchartium\///g" | sed "s/\.h/\.h \\\/g"
HEADERS += \
    src/qtchartium/axis/barcategoryaxis/chartiumbarcategoryaxis.h \
    src/qtchartium/axis/barcategoryaxis/chartiumbarcategoryaxisx.h \
    src/qtchartium/axis/barcategoryaxis/chartiumbarcategoryaxisy.h \
    src/qtchartium/axis/barcategoryaxis/ichartiumbarcategoryaxis.h \
    src/qtchartium/axis/barcategoryaxis/ichartiumbarcategoryaxisx.h \
    src/qtchartium/axis/barcategoryaxis/ichartiumbarcategoryaxisy.h \
    src/qtchartium/axis/chartiumaxis.h \
    src/qtchartium/axis/chartiumaxiselement.h \
    src/qtchartium/axis/chartiumcartesianaxis.h \
    src/qtchartium/axis/chartiumeditableaxislabel.h \
    src/qtchartium/axis/chartiumhorizontalaxis.h \
    src/qtchartium/axis/chartiumlinearrowitem.h \
    src/qtchartium/axis/chartiumverticalaxis.h \
    src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxis.h \
    src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxislabel.h \
    src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxisx.h \
    src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxisy.h \
    src/qtchartium/axis/datetimeaxis/ichartiumdatetimeaxis.h \
    src/qtchartium/axis/datetimeaxis/ichartiumdatetimeaxislabel.h \
    src/qtchartium/axis/datetimeaxis/ichartiumdatetimeaxisx.h \
    src/qtchartium/axis/datetimeaxis/ichartiumdatetimeaxisy.h \
    src/qtchartium/axis/ichartiumaxis.h \
    src/qtchartium/axis/ichartiumaxiselement.h \
    src/qtchartium/axis/ichartiumcartesianaxis.h \
    src/qtchartium/axis/ichartiumeditableaxislabel.h \
    src/qtchartium/axis/ichartiumhorizontalaxis.h \
    src/qtchartium/axis/ichartiumlinearrowitem.h \
    src/qtchartium/axis/ichartiumverticalaxis.h \
    src/qtchartium/axis/valueaxis/chartiumvalueaxis.h \
    src/qtchartium/axis/valueaxis/chartiumvalueaxislabel.h \
    src/qtchartium/axis/valueaxis/chartiumvalueaxisx.h \
    src/qtchartium/axis/valueaxis/chartiumvalueaxisy.h \
    src/qtchartium/axis/valueaxis/ichartiumvalueaxis.h \
    src/qtchartium/axis/valueaxis/ichartiumvalueaxislabel.h \
    src/qtchartium/axis/valueaxis/ichartiumvalueaxisx.h \
    src/qtchartium/axis/valueaxis/ichartiumvalueaxisy.h \
    src/qtchartium/chartiumbackground.h \
    src/qtchartium/chartiumchart.h \
    src/qtchartium/chartiumdataset.h \
    src/qtchartium/chartiumelement.h \
    src/qtchartium/chartiumhelpers.h \
    src/qtchartium/chartiumitem.h \
    src/qtchartium/chartiumpresenter.h \
    src/qtchartium/chartiumtitle.h \
    src/qtchartium/chartiumview.h \
    src/qtchartium/charts/chartiumseries.h \
    src/qtchartium/charts/ichartiumseries.h \
    src/qtchartium/charts/linechart/chartiumlinechartitem.h \
    src/qtchartium/charts/linechart/chartiumlineseries.h \
    src/qtchartium/charts/linechart/ichartiumlinechartitem.h \
    src/qtchartium/charts/linechart/ichartiumlineseries.h \
    src/qtchartium/charts/xychart/chartiumxychart.h \
    src/qtchartium/charts/xychart/chartiumxyseries.h \
    src/qtchartium/charts/xychart/ichartiumxychart.h \
    src/qtchartium/charts/xychart/ichartiumxyseries.h \
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
    src/qtchartium/ichartiumtitle.h \
    src/qtchartium/ichartiumview.h \
    src/qtchartium/layout/chartiumcartesianlayout.h \
    src/qtchartium/layout/chartiumlayout.h \
    src/qtchartium/layout/ichartiumcartesianlayout.h \
    src/qtchartium/layout/ichartiumlayout.h \
    src/qtchartium/legend/chartiumlegend.h \
    src/qtchartium/legend/chartiumlegendmarker.h \
    src/qtchartium/legend/chartiumlegendmarkerxy.h \
    src/qtchartium/legend/chartiumlegendscroller.h \
    src/qtchartium/legend/ichartiumlegend.h \
    src/qtchartium/legend/ichartiumlegendmarker.h \
    src/qtchartium/legend/ichartiumlegendmarkerxy.h \
    src/qtchartium/legend/ichartiumlegendscroller.h \
    src/qtchartium/legend/scroller/chartiumscroller.h \
    src/qtchartium/legend/scroller/chartiumscrollticker.h \
    src/qtchartium/legend/scroller/ichartiumscroller.h \
    src/qtchartium/legend/scroller/ichartiumscrollticker.h \
    src/qtchartium/themes/chartiumtheme.h \
    src/qtchartium/themes/chartiumthememanager.h \
    src/qtchartium/themes/custom/chartiumthemecustomdark.h \
    src/qtchartium/themes/ichartiumtheme.h \
    src/qtchartium/themes/ichartiumthememanager.h \
    src/qtchartium/themes/qtcharts/chartiumthemebluecerulean.h \
    src/qtchartium/themes/qtcharts/chartiumthemeblueicy.h \
    src/qtchartium/themes/qtcharts/chartiumthemebluencs.h \
    src/qtchartium/themes/qtcharts/chartiumthemebrownsand.h \
    src/qtchartium/themes/qtcharts/chartiumthemedark.h \
    src/qtchartium/themes/qtcharts/chartiumthemehighcontrast.h \
    src/qtchartium/themes/qtcharts/chartiumthemelight.h \
    src/qtchartium/themes/qtcharts/chartiumthemeqt.h \
