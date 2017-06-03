cmake_minimum_required( VERSION 3.7 )

project( yans-engine CXX )

find_package( Qt5 COMPONENTS Core REQUIRED )

configure_file( yans-engine.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/yans-engine.h
    @ONLY
)

include( cmake/source.cmake )

list( APPEND YANS_ENGINE_HEADERS
    ${CMAKE_CURRENT_BINARY_DIR}/include/yans-engine.h
)

add_library( ${PROJECT_NAME} SHARED
    ${YANS_ENGINE_SOURCES}
    ${YANS_ENGINE_HEADERS}
)

target_compile_definitions( ${PROJECT_NAME}
    PRIVATE
        YANS_BUILD_ENGINE_LIB
)

target_include_directories( ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries( ${PROJECT_NAME}
    Qt5::Core
)
