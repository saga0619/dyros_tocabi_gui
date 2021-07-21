cmake_minimum_required(VERSION 3.5.0)
project(tocabi_gui)

add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rqt_gui
  rqt_gui_cpp
  sensor_msgs
  std_msgs
  geometry_msgs
  tocabi_msgs  
)



if($ENV{ROS_DISTRO} STREQUAL "melodic")
  message("Using ROS melodic")

  find_package(Qt5 REQUIRED Core Widgets X11Extras Gui)

  ADD_DEFINITIONS(-DCOMPILE_MELODIC)

elseif($ENV{ROS_DISTRO} STREQUAL "kinetic")
  message("Using ROS kinetic")
  find_package(Qt5 REQUIRED Core Widgets)

  ADD_DEFINITIONS(-DCOMPILE_KINETIC)

else()
  message("Unknown ROS distro:")
  message($ENV{ROS_DISTRO})
endif()

set(CMAKE_AUTOMOC ON)
catkin_python_setup()

catkin_package(
# INCLUDE_DIRS ${tocabi_gui_INCLUDE_DIRECTORIES}
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp rqt_gui rqt_gui_cpp sensor_msgs std_msgs geometry_msgs tocabi_msgs
#  DEPENDS system_lib
)



set(tocabi_gui_SRCS
  src/tocabi_gui.cpp
)

set(tocabi_gui_HDRS
  include/tocabi_gui/tocabi_gui.h
)

set(tocabi_gui_UIS
  src/tocabi_gui.ui
)

set(qxtglobalshortcut
  core/qxtglobal.cpp
  gui/qxtwindowsystem.cpp
  gui/qxtglobalshortcut.cpp
  gui/qxtwindowsystem_x11.cpp
  gui/qxtglobalshortcut_x11.cpp
)


qt5_wrap_cpp(tocabi_gui_MOCS ${tocabi_gui_HDRS})
qt5_wrap_ui(tocabi_gui_UIS_H ${tocabi_gui_UIS})


###########
## Build ##
###########

if($ENV{ROS_DISTRO} STREQUAL "melodic")
  include_directories(
    include
    core
    gui
    ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}/..
    ${catkin_INCLUDE_DIRS}
  )

  add_library(${PROJECT_NAME}
    ${tocabi_gui_SRCS}
    ${tocabi_gui_MOCS}
    ${tocabi_gui_UIS_H}
    ${qxtglobalshortcut}
  )

  target_link_libraries(${PROJECT_NAME}
    ${catkin_LIBRARIES}
  )

  target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui Qt5::X11Extras Qt5::GuiPrivate)

elseif($ENV{ROS_DISTRO} STREQUAL "kinetic")
  include_directories(
    include
    core
    gui
    ${CMAKE_CURRENT_BINARY_DIR}/..
    ${catkin_INCLUDE_DIRS}
  )

  add_library(${PROJECT_NAME}
    ${tocabi_gui_SRCS}
    ${tocabi_gui_MOCS}
    ${tocabi_gui_UIS_H}
  )

  target_link_libraries(${PROJECT_NAME}
    ${catkin_LIBRARIES}
  )

  target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui)
endif()


add_dependencies(${PROJECT_NAME} ${catkin_EXPORTED_TARGETS})