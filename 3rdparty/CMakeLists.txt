cmake_minimum_required( VERSION 3.7 )

include( ExternalProject )

externalproject_add( glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.8.4
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}/glm"
    UPDATE_COMMAND ""
    CMAKE_ARGS
        "-G${CMAKE_GENERATOR}"
        "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DCMAKE_VERBOSE_MAKEFILE:BOOLEAN=ON"
        "-DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/install"
)

list( INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_BINARY_DIR}/install/lib/cmake" )
list( INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_BINARY_DIR}/install/lib64/cmake" )
