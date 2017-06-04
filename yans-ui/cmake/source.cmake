cmake_minimum_required( VERSION 3.7 )

set( YANS_UI_SOURCES )
set( YANS_UI_HEADERS )
mark_as_advanced(
    YANS_UI_SOURCES
    YANS_UI_HEADERS
)

include( cmake/source/render.cmake )
include( cmake/source/quick.cmake )

list( APPEND YANS_UI_SOURCES
    src/YansUIPlugin.cpp
)

list( APPEND YANS_UI_HEADERS
    src/YansUIPlugin.h
)
