cmake_minimum_required( VERSION 3.7 )

project( yans-launcher CXX )

find_package( glm 0.9.8 REQUIRED )
find_package( Qt5 COMPONENTS Core Gui Quick REQUIRED )

set( SOURCES
    src/main.cpp
)

qt5_add_resources( RESOURCES yans-launcher.qrc )

add_executable( ${PROJECT_NAME}
    ${SOURCES}
    ${RESOURCES}
)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries( ${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Quick
    GL
)
