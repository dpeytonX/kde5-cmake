project (sample)

set (project_name sample)

cmake_minimum_required (VERSION 2.8.11)
set_property (GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#If you include plasma uncomment these two lines
#find_package(ECM REQUIRED NO_MODULE)
#set(CMAKE_MODULE_PATH ${ECM_KDE_MODULE_DIR})

#Qt requirements
find_package (Qt5Core REQUIRED)
get_target_property (QtCore_location Qt5::Core LOCATION)
find_package (Qt5Gui REQUIRED)
get_target_property (QtGui_location Qt5::Gui LOCATION)
find_package (Qt5Qml REQUIRED)
get_target_property (QtQml_location Qt5::Qml LOCATION)
find_package (Qt5Quick REQUIRED)
get_target_property (QtQuick_location Qt5::Quick LOCATION)
find_package (KF5Declarative REQUIRED)
get_target_property(KDeclarative_location KF5::Declarative LOCATION)
#If you see cannot find ECMConfig.cmake install
#project-neon5-extra-cmake-modules
#
#find_package (KF5Plasma REQUIRED)
#get_target_property(Plasma_location KF5::Plasma LOCATION)
#find_package (KF5PlasmaQuick REQUIRED)
#get_target_property(PlasmaQuick_location KF5::PlasmaQuick LOCATION)


set (sample_VERSION_MAJOR 1)
set (sample_VERSION_MINOR 0)

set (PROJECT_SOURCE_DIR "src/main")
set (PROJECT_RESOURCE_DIR "src/main/resources")
set (PROJECT_TEST_DIR "src/test")

configure_file (
  "${PROJECT_SOURCE_DIR}/${project_name}.h.in"
  "${PROJECT_BINARY_DIR}/${project_name}.h"
  )
  
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

#sub directories
#add_subdirectory ("${PROJECT_SOURCE_DIR}/models")

set (project_SOURCES "${PROJECT_SOURCE_DIR}/main.cpp")
set (project_MOC_HEADERS) # Qt Objects
set (project_HEADER ${project_MOC_HEADERS} "${PROJECT_BINARY_DIR}/${project_name}.h")
set (project_RESOURCES "${PROJECT_RESOURCE_DIR}/qml.qrc")

set (project_DESKTOP "${PROJECT_RESOURCE_DIR}/desktop/${project_name}.desktop")
set (project_ICONS "${PROJECT_RESOURCE_DIR}/icons/${project_name}.svg")

qt5_wrap_cpp(project_MOC ${project_MOC_HEADERS})
qt5_add_resources(project_RESOURCES_RCC ${project_RESOURCES})
add_executable (${project_name} ${project_SOURCES} ${project_HEADER} ${project_RESOURCES_RCC} ${project_MOC})

#Linking Options
target_link_libraries (${project_name} Qt5::Core)
target_link_libraries (${project_name} Qt5::Gui)
target_link_libraries (${project_name} Qt5::Qml)
target_link_libraries (${project_name} Qt5::Quick)
target_link_libraries (${project_name} KF5::Declarative)
#target_link_libraries (${project_name} KF5::Plasma)
#target_link_libraries (${project_name} KF5::PlasmaQuick)


#testing
message ("CMAKE_BUILD_TYPE = " ${CMAKE_BUILD_TYPE})
if ("${CMAKE_BUILD_TYPE}" STREQUAL TEST)
  enable_testing()

  # Tell CMake to run moc when necessary:
  set(CMAKE_AUTOMOC ON)

  # As moc files are generated in the binary dir, tell CMake
  # to always look for includes there:
  set(CMAKE_INCLUDE_CURRENT_DIR ON)

  find_package(Qt5Test REQUIRED)
  get_target_property (QtTest_location Qt5::Test LOCATION)
  
  set (t_SOURCES "${project_SOURCES}")
  set (t_MOC_HEADERS "${project_MOC_HEADERS}")
  set (t_HEADERS ${t_MOC_HEADERS})
  
  macro(qt5_add_test test_name test_file test_sources test_headers test_moc_headers)
    add_executable(${test_name} ${test_file} ${test_sources} ${test_headers})
    add_test(${test_name} ${test_name})
    target_link_libraries (${test_name} Qt5::Test)
    target_link_libraries (${test_name} Qt5::Core)
    target_link_libraries (${test_name} Qt5::Gui)
    target_link_libraries (${test_name} Qt5::Qml)
    target_link_libraries (${test_name} Qt5::Quick)
    target_link_libraries (${test_name} KF5::Declarative)
  endmacro(qt5_add_test)
  
  qt5_add_test (locatetest "${PROJECT_TEST_DIR}/test.cpp" ${t_SOURCES} ${t_HEADERS} ${t_MOC_HEADERS})
endif()


install (TARGETS ${project_name} DESTINATION bin)
install (FILES ${project_HEADER} DESTINATION include/${project_name})
install (FILES ${project_DESKTOP} DESTINATION share/applications)
install (FILES ${project_ICONS} DESTINATION share/icons/hicolor/scalable/apps)
