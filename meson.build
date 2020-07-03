project('bdsup2sub++', 'cpp', version : '1.0.3', default_options : ['warning_level=3'])

add_global_arguments(['-DBUILD_QXT_CORE', '-DQT_NO_DEBUG', '-DQT_XML_LIB', '-DQT_WIDGETS_LIB', '-DQT_GUI_LIB', '-DQT_CORE_LIB'], language: 'cpp')

incdirs = [
    include_directories('src'),
    include_directories('src/Filters'),
    include_directories('src/Subtitles'),
    include_directories('src/Tools')
]

source_files = [
    files('src/bdsup2sub.cpp'),
    files('src/zoomableimagearea.cpp'),
    files('src/editpane.cpp'),
    files('src/Filters/trianglefilter.cpp'),
    files('src/Filters/mitchellfilter.cpp'),
    files('src/Filters/lanczos3filter.cpp'),
    files('src/Filters/hermitefilter.cpp'),
    files('src/Filters/bsplinefilter.cpp'),
    files('src/Filters/bicubicfilter.cpp'),
    files('src/Filters/bellfilter.cpp'),
    files('src/Filters/filterop.cpp'),
    files('src/Subtitles/subdvd.cpp'),
    files('src/Subtitles/palette.cpp'),
    files('src/Subtitles/bitmap.cpp'),
    files('src/Subtitles/subtitleprocessor.cpp'),
    files('src/Subtitles/subpicture.cpp'),
    files('src/Subtitles/erasepatch.cpp'),
    files('src/Subtitles/subpicturedvd.cpp'),
    files('src/Subtitles/imageobjectfragment.cpp'),
    files('src/progressdialog.cpp'),
    files('src/Subtitles/supdvd.cpp'),
    files('src/Tools/filebuffer.cpp'),
    files('src/conversiondialog.cpp'),
    files('src/Filters/filters.cpp'),
    files('src/Subtitles/palettebitmap.cpp'),
    files('src/Tools/timeutil.cpp'),
    files('src/Subtitles/suphd.cpp'),
    files('src/Subtitles/supbd.cpp'),
    files('src/Subtitles/subpicturebd.cpp'),
    files('src/Subtitles/paletteinfo.cpp'),
    files('src/Subtitles/substreamdvd.cpp'),
    files('src/Subtitles/subpicturehd.cpp'),
    files('src/Tools/bitstream.cpp'),
    files('src/Subtitles/supxml.cpp'),
    files('src/Subtitles/subpicturexml.cpp'),
    files('src/Tools/quantizefilter.cpp'),
    files('src/exportdialog.cpp'),
    files('src/Tools/numberutil.cpp'),
    files('src/editdialog.cpp'),
    files('src/helpdialog.cpp'),
    files('src/colordialog.cpp'),
    files('src/framepalettedialog.cpp'),
    files('src/movedialog.cpp'),
    files('src/Subtitles/imageobject.cpp'),
    files('src/qxtglobal.cpp'),
    files('src/qxtcommandoptions.cpp'),
]

qt5_mod = import('qt5')
qt5deps = dependency('qt5', modules : ['Widgets', 'Core', 'Xml'])

cxx = meson.get_compiler('cpp')
cpu_family = target_machine.cpu_family()
host_system = target_machine.system()

win_dep = []

if host_system == 'windows'
    mxe_qt5 = get_option('prefix') + '/qt5'

    win_dep += cxx.find_library('qwindows', dirs: mxe_qt5 / 'plugins/platforms')
    deps = [
        'Qt5ThemeSupport',
        'Qt5EventDispatcherSupport',
        'Qt5FontDatabaseSupport',
        'Qt5WindowsUIAutomationSupport',
        'wtsapi32'
    ]
    foreach d : deps
        win_dep += cxx.find_library(d, dirs: mxe_qt5 / 'lib')
    endforeach
endif

moc_header_files = [
    'src/bdsup2sub.h',
    'src/colordialog.h',
    'src/conversiondialog.h',
    'src/editdialog.h',
    'src/editpane.h',
    'src/exportdialog.h',
    'src/framepalettedialog.h',
    'src/helpdialog.h',
    'src/movedialog.h',
    'src/progressdialog.h',
    'src/Subtitles/subdvd.h',
    'src/Subtitles/subtitleprocessor.h',
    'src/Subtitles/supbd.h',
    'src/Subtitles/supdvd.h',
    'src/Subtitles/suphd.h',
    'src/Subtitles/supxml.h',
    'src/zoomableimagearea.h'
]

ui_file_list = [
    'src/bdsup2sub.ui',
    'src/colordialog.ui',
    'src/conversiondialog.ui',
    'src/editdialog.ui',
    'src/exportdialog.ui',
    'src/framepalettedialog.ui',
    'src/helpdialog.ui',
    'src/movedialog.ui',
    'src/progressdialog.ui',
]

qtprocessed = qt5_mod.preprocess(moc_headers: moc_header_files,
                                 ui_files: ui_file_list,
                                 include_directories: incdirs)

pkg_mod = import('pkgconfig')

libbdsup2sub = static_library(
    'bdsup2sub++',

    source_files,

    qtprocessed,

    include_directories: incdirs,

    dependencies: qt5deps,

    install : true
)

pkg_mod.generate(libraries: libbdsup2sub,
                 version: meson.project_version(),
                 name: 'libbdsup2sub++',
                 filebase: 'bdsup2sub++',
                 description: 'Pretty much bdsup2sub++ without the main function.')

install_headers('src/Subtitles/palette.h', subdir: 'bdsup2sub/Subtitles')
install_headers('src/bdsup2sub.h', subdir: 'bdsup2sub')

executable(
    'bdsup2sub++',

    'src/main.cpp',

    qtprocessed,

    link_with: libbdsup2sub,

    include_directories: incdirs,

    dependencies: [qt5deps, win_dep],

    install : true
)
