cmake_minimum_required( VERSION 3.7 )

set( YANS_ENGINE_SOURCES )
set( YANS_ENGINE_HEADERS )
mark_as_advanced(
    YANS_ENGINE_SOURCES
    YANS_ENGINE_HEADERS
)

include( cmake/source/biota.cmake )
include( cmake/source/data.cmake )
