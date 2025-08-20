cmake_minimum_required(VERSION 3.19)
project(muri LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 11)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

include(FetchContent)

#
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2
  GIT_TAG v3.9.1  # Change as needed
)

FetchContent_MakeAvailable(catch2)
#

#
FetchContent_Declare(
  Eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG master
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE)
# note: To disable eigen tests,
# you should put this code in a add_subdirectory to avoid to change
# BUILD_TESTING for your own project too since variables are directory
# scoped
set(BUILD_TESTING OFF)
set(EIGEN_BUILD_TESTING OFF)
set(EIGEN_MPL2_ONLY ON)
set(EIGEN_BUILD_PKGCONFIG OFF)
set(EIGEN_BUILD_DOC OFF)
FetchContent_MakeAvailable(Eigen)
#

qt_standard_project_setup()

# specify that there is anexecutable and required sources
qt_add_executable(${PROJECT_NAME}
    WIN32 MACOSX_BUNDLE

    main.cpp

    include/gvar.h

    include/mainwindow.h
    src/mainwindow.cpp

    src/mainwindow.ui

    preprocessor/include/grid.h
    preprocessor/src/grid.cpp
)

qt_add_executable(tests
    preprocessor/include/grid.h
    preprocessor/src/grid.cpp
    preprocessor/tests/grid_test.cpp
)

# define where the headers are
target_include_directories(${PROJECT_NAME} PUBLIC
    include
    preprocessor/include
    eigen-3.4.0
)

target_include_directories(tests PUBLIC
    include
    preprocessor/include
    eigen-3.4.0
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt::Core
        Qt::Widgets
        Eigen3::Eigen#
)

target_link_libraries(tests
    PRIVATE
        Catch2::Catch2WithMain
        Eigen3::Eigen)

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
