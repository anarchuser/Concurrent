cmake_minimum_required(VERSION 3.12.4)
project(Concurrent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_REQUIRED_LIBRARIES "-lglog -pthread")
set(CMAKE_CXX_FLAGS "-fconcepts -fcoroutines")

file(GLOB_RECURSE SRCS ${PROJECT_SOURCE_DIR}/src/*)
file(GLOB_RECURSE LIBS ${PROJECT_SOURCE_DIR}/lib/*)
add_executable(Concurrent src/main.cpp config.h ${SRCS} ${LIBS})

find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
target_link_libraries(Concurrent Threads::Threads)
target_link_libraries(Concurrent glog)

find_package(Catch2 CONFIG)
IF (Catch2_FOUND)
    file(GLOB_RECURSE TEST_SRCS ${PROJECT_SOURCE_DIR}/test/*.c* ${PROJECT_SOURCE_DIR}/src/functions.cpp)
    add_executable(Test ${GEN_PROTO_FILES} ${TEST_SRCS} ${LIBS})

    add_compile_definitions(Test PRIVATE ERRORS_AS_WARNINGS)

    target_link_libraries(Test PRIVATE Catch2::Catch2)
    include(CTest)
    include(Catch)
    catch_discover_tests(Test)

    target_link_libraries(Test PRIVATE Threads::Threads)
    target_link_libraries(Test PRIVATE glog)
ENDIF()