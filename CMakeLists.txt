cmake_minimum_required(VERSION 3.19)
project(muri LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

# specify that there is anexecutable and required sources
qt_add_executable(muri
    WIN32 MACOSX_BUNDLE
    main.cpp
    src/mainwindow.cpp
    include/mainwindow.h
    src/mainwindow.ui
)

# define where the headers are
target_include_directories(muri PUBLIC include)

target_link_libraries(muri
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS muri
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET muri
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
