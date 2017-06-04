cmake_minimum_required( VERSION 3.7 )

project( yans-ui CXX )

set( YANS_UI_VERSION_MAJOR 1 )
set( YANS_UI_VERSION_MINOR 0 )
set( YANS_UI_VERSION
    ${YANS_UI_VERSION_MAJOR}.${YANS_UI_VERSION_MINOR}
)

configure_file( yans-ui.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/yans-ui.h
    @ONLY
)

configure_file( qmldir.in
    ${yans-launcher_BINARY_DIR}/yans/ui/qmldir
    @ONLY
)

find_package( Qt5 COMPONENTS Core Gui Quick REQUIRED )

qt5_add_resources( YANS_UI_RESOURCES shaders.qrc )

include( cmake/source.cmake )

list( APPEND YANS_UI_HEADERS
    ${CMAKE_CURRENT_BINARY_DIR}/include/yans-ui.h
)

add_library( ${PROJECT_NAME} SHARED
    ${YANS_UI_SOURCES}
    ${YANS_UI_HEADERS}
    ${YANS_UI_RESOURCES}
)

target_compile_definitions( ${PROJECT_NAME}
    PRIVATE
        YANS_BUILD_UI_LIB
)

target_include_directories( ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries( ${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Quick
)
