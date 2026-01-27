cmake_minimum_required(VERSION 3.16)
project(bdsup2sub++ VERSION 1.0.4 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  # Git auto-ignore out-of-source build directory
  file(GENERATE OUTPUT .gitignore CONTENT "*")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Xml)

add_executable(bdsup2sub++
  src/Filters/bellfilter.cpp
  src/Filters/bicubicfilter.cpp
  src/Filters/bsplinefilter.cpp
  src/Filters/filters.cpp
  src/Filters/hermitefilter.cpp
  src/Filters/lanczos3filter.cpp
  src/Filters/mitchellfilter.cpp
  src/Filters/trianglefilter.cpp
  src/Filters/filterop.cpp
  src/Subtitles/erasepatch.cpp
  src/Subtitles/imageobject.cpp
  src/Subtitles/imageobjectfragment.cpp
  src/Subtitles/palettebitmap.cpp
  src/Subtitles/paletteinfo.cpp
  src/Subtitles/subpicture.cpp
  src/Subtitles/subpicturehd.cpp
  src/Subtitles/subpicturexml.cpp
  src/Subtitles/bitmap.cpp
  src/Subtitles/palette.cpp
  src/Subtitles/subdvd.cpp
  src/Subtitles/subpicturebd.cpp
  src/Subtitles/subpicturedvd.cpp
  src/Subtitles/substreamdvd.cpp
  src/Subtitles/subtitleprocessor.cpp
  src/Subtitles/supbd.cpp
  src/Subtitles/supdvd.cpp
  src/Subtitles/suphd.cpp
  src/Subtitles/supxml.cpp
  src/Tools/filebuffer.cpp
  src/Tools/bitstream.cpp
  src/Tools/numberutil.cpp
  src/Tools/quantizefilter.cpp
  src/Tools/timeutil.cpp
  src/bdsup2sub.ui
  src/colordialog.ui
  src/conversiondialog.ui
  src/editdialog.ui
  src/exportdialog.cpp
  src/exportdialog.ui
  src/framepalettedialog.ui
  src/helpdialog.cpp
  src/helpdialog.ui
  src/movedialog.cpp
  src/movedialog.ui
  src/progressdialog.cpp
  src/progressdialog.ui
  src/zoomableimagearea.cpp
  src/colordialog.cpp
  src/conversiondialog.cpp
  src/editdialog.cpp
  src/editpane.cpp
  src/framepalettedialog.cpp
  src/main.cpp
  src/bdsup2sub.cpp
  src/bdsup2sub.qrc
  src/bdsup2sub.rc
)

if (CMAKE_CXX_COMPILER_ID MATCHES "(Clang|GNU)")                              
  #target_compile_options(bdsup2sub++ PRIVATE -Wall -Wpedantic -Wextra -Werror)                       
  #target_compile_options(bdsup2sub++ PRIVATE -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer)
  #target_link_options(bdsup2sub++ PRIVATE -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")                                 
  set_property(DIRECTORY APPEND PROPERTY COMPILE_OPTIONS "/w")                
endif()

add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0xFFFFFF)

target_include_directories(bdsup2sub++ PUBLIC src)

target_link_libraries(bdsup2sub++
  Qt::Core
  Qt::Widgets
  Qt::Xml
)
