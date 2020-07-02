#-------------------------------------------------
#
# Project created by QtCreator 2011-12-26T16:10:17
#
#-------------------------------------------------

#check Qt version
QT_VERSION = $$[QT_VERSION]
QT_VERSION = $$split(QT_VERSION, ".")
QT_VER_MAJ = $$member(QT_VERSION, 0)

QT        += core xml
lessThan(QT_VER_MAJ, 4) {
QT        += gui
}
greaterThan(QT_VER_MAJ, 4) {
QT        -= gui
QT        += widgets
}
CONFIG    += qt console sharedlib create_pc create_prl no_install_prl
DEFINES   += BUILD_QXT_CORE
QMAKE_CXXFLAGS += -std=c++14
TARGET     = bdsup2sub++
TEMPLATE   = lib
header_bdsup2sub.path = /usr/include/bdsup2sub++/
header_bdsup2sub.files = $$PWD/bdsup2sub.h
header_pallet.path = /usr/include/bdsup2sub++/Subtitles
header_pallet.files = $$PWD/Subtitles/palette.h
target.path = $$[QT_INSTALL_LIBS]
QMAKE_PKGCONFIG_NAME = bdsup2sub++
QMAKE_PKGCONFIG_DESCRIPTION = Basically bdsup2sub++ without main.cpp
QMAKE_PKGCONFIG_PREFIX = $$INSTALLBASE
QMAKE_PKGCONFIG_LIBDIR = $$target.path
QMAKE_PKGCONFIG_INCDIR = $$header_bdsup2sub.path
QMAKE_PKGCONFIG_VERSION = 1.0.3
QMAKE_PKGCONFIG_DESTDIR = pkgconfig
INSTALLS += target header_pallet header_bdsup2sub

SOURCES += bdsup2sub.cpp \
    zoomableimagearea.cpp \
    editpane.cpp \
    Filters/trianglefilter.cpp \
    Filters/mitchellfilter.cpp \
    Filters/lanczos3filter.cpp \
    Filters/hermitefilter.cpp \
    Filters/bsplinefilter.cpp \
    Filters/bicubicfilter.cpp \
    Filters/bellfilter.cpp \
    Filters/filterop.cpp \
    Subtitles/subdvd.cpp \
    Subtitles/palette.cpp \
    Subtitles/bitmap.cpp \
    Subtitles/subtitleprocessor.cpp \
    Subtitles/subpicture.cpp \
    Subtitles/erasepatch.cpp \
    Subtitles/subpicturedvd.cpp \
    Subtitles/imageobjectfragment.cpp \
    progressdialog.cpp \
    Subtitles/supdvd.cpp \
    Tools/filebuffer.cpp \
    conversiondialog.cpp \
    Filters/filters.cpp \
    Subtitles/palettebitmap.cpp \
    Tools/timeutil.cpp \
    Subtitles/suphd.cpp \
    Subtitles/supbd.cpp \
    Subtitles/subpicturebd.cpp \
    Subtitles/paletteinfo.cpp \
    Subtitles/substreamdvd.cpp \
    Subtitles/subpicturehd.cpp \
    Tools/bitstream.cpp \
    Subtitles/supxml.cpp \
    Subtitles/subpicturexml.cpp \
    Tools/quantizefilter.cpp \
    exportdialog.cpp \
    Tools/numberutil.cpp \
    editdialog.cpp \
    helpdialog.cpp \
    colordialog.cpp \
    framepalettedialog.cpp \
    movedialog.cpp \
    Subtitles/imageobject.cpp \
    qxtglobal.cpp \
    qxtcommandoptions.cpp

HEADERS  += bdsup2sub.h \
    zoomableimagearea.h \
    editpane.h \
    types.h \
    Filters/trianglefilter.h \
    Filters/mitchellfilter.h \
    Filters/lanczos3filter.h \
    Filters/hermitefilter.h \
    Filters/filter.h \
    Filters/bsplinefilter.h \
    Filters/bicubicfilter.h \
    Filters/bellfilter.h \
    Filters/filterop.h \
    Subtitles/substream.h \
    Subtitles/substreamdvd.h \
    Subtitles/subdvd.h \
    Subtitles/palette.h \
    Subtitles/bitmap.h \
    Subtitles/subtitleprocessor.h \
    Subtitles/subpicture.h \
    Subtitles/erasepatch.h \
    Subtitles/subpicturedvd.h \
    Subtitles/imageobjectfragment.h \
    progressdialog.h \
    Subtitles/supdvd.h \
    Tools/filebuffer.h \
    conversiondialog.h \
    Filters/filters.h \
    Subtitles/palettebitmap.h \
    Tools/timeutil.h \
    Subtitles/suphd.h \
    Subtitles/supbd.h \
    Subtitles/subpicturebd.h \
    Subtitles/imageobject.h \
    Subtitles/paletteinfo.h \
    Subtitles/subpicturehd.h \
    Tools/bitstream.h \
    Subtitles/supxml.h \
    Subtitles/subpicturexml.h \
    Tools/quantizefilter.h \
    exportdialog.h \
    Tools/numberutil.h \
    editdialog.h \
    helpdialog.h \
    colordialog.h \
    framepalettedialog.h \
    movedialog.h \
    qxtglobal.h \
    qxtcommandoptions.h

FORMS    += bdsup2sub.ui \
    progressdialog.ui \
    conversiondialog.ui \
    exportdialog.ui \
    editdialog.ui \
    helpdialog.ui \
    colordialog.ui \
    framepalettedialog.ui \
    movedialog.ui

RESOURCES += \
    bdsup2sub.qrc

RC_FILE = bdsup2sub.rc
