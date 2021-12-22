cmake_minimum_required(VERSION 3.21)
project(bosstime)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif ()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(Tcmalloc)
find_package(Threads)
find_package(OpenSSL)
find_package(Boost COMPONENTS system thread REQUIRED)

if (OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif ()

find_program(CCACHE_FOUND ccache)
if (CCACHE_FOUND)
    message("Found ccache ${CCACHE_FOUND}")
    message("Using ccache to speed up compilation")
    set(ENV{CCACHE_CPP2} "yes")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif (CCACHE_FOUND)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif ()

include_directories(${Boost_INCLUDE_DIR})

set(PROJECT_INCLUDE_DIR
        ${PROJECT_SOURCE_DIR}/include
        )

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

add_library(bosstime_webserver src/bosstime.cpp)
target_link_libraries(bosstime_webserver ${Boost_LIBRARIES})
target_link_libraries(bosstime_webserver ${CMAKE_THREAD_LIBS_INIT})

add_executable(bosstime_main src/bosstime_main.cpp)
target_link_libraries(bosstime_main bosstime_webserver)
#target_link_libraries(bosstime_main ${Boost_LIBRARIES})


