cmake_minimum_required( VERSION 3.7 )

project( yans CXX )

set( YANS_VERSION_MAJOR 0 )
set( YANS_VERSION_MINOR 0 )
set( YANS_VERSION_PATCH 1 )
set( YANS_VERSION
    ${YANS_VERSION_MAJOR}.${YANS_VERSION_MINOR}.${YANS_VERSION_PATCH}
)

set( CMAKE_AUTOMOC ON )
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_STANDARD_REQUIRED 14 )

add_subdirectory( 3rdparty )

add_subdirectory( yans-engine )
add_subdirectory( yans-ui )
add_subdirectory( yans-launcher )

