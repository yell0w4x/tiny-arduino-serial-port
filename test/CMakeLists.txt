cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

if ( CMAKE_COMPILER_IS_GNUCC )
  add_definitions ("-Wall")
  add_definitions ("-Wextra")
  add_definitions ("-Werror")
  add_definitions ("-Wfatal-errors")
  add_definitions ("-std=gnu++14")
endif ( CMAKE_COMPILER_IS_GNUCC )

find_package(Threads)
find_package(GTest REQUIRED)
find_package(GMock REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
include_directories(.)
include_directories(../include)

enable_testing()

add_executable(container_test container_test.cpp)
target_link_libraries(container_test ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
add_test(container_test container_test)

