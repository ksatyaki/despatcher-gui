cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
project(despatcher-gui)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
 
qt4_wrap_ui(UISrcs despatcher_gui.ui)
qt4_wrap_cpp(MOCSrcs despatcher_gui.h)
 
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_executable(despatcher-gui main.cpp despatcher_gui.cpp ${MOCSrcs} ${UISrcs})
target_link_libraries(despatcher-gui ${QT_LIBRARIES} peiskernel peiskernel_mt)