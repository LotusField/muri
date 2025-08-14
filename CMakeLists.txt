cmake_minimum_required(VERSION 3.19)
project(muri LANGUAGES CXX VERSION 0.0.1)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package (Eigen3 3.4 REQUIRED NO_MODULE) #

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

# define where the headers are
target_include_directories(${PROJECT_NAME} PUBLIC
    include
    preprocessor/include
    "eigen-3.4.0"
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt::Core
        Qt::Widgets
        ${Eigen_LIBRARIES} #
)

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
