cmake_minimum_required(VERSION 2.8.11)
  project(ship_test)
  enable_testing()

# replace XX with the version you have
  set(Boost_ADDITIONAL_VERSIONS "1.55" "1.55.0")

# finds boost, triggers an error otherwise
  find_package(Boost 1.55 REQUIRED COMPONENTS unit_test_framework)

if(Boost_FOUND)
      message("Boost Found")
else()
      error("Boost Not Found")
endif()

# indicates the location of the boost installation tree.
# hard-coded for our simple example.
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(BOOST_INCLUDE_DIRS $boost_installation_prefix/include)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# creates the executable
file(GLOB TEST_SOURCES
ship_impl.h
ship_impl.cpp
ship_tests.cpp
)
add_executable(test_executable ${TEST_SOURCES})
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
# indicates the include paths
target_include_directories(test_executable PRIVATE ${Boost_INCLUDE_DIRS})
# indicates the shared library variant
target_compile_definitions(test_executable PRIVATE "BOOST_TEST_DYN_LINK=1")
# indicates the link paths
target_link_libraries(test_executable ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

# declares a test with our executable
add_test(NAME test1 COMMAND test_executable)

file(GLOB SOURCES
ship_impl.h
ship_impl.cpp
ship_exe.cpp
)
add_executable(ship_exec ${SOURCES})
