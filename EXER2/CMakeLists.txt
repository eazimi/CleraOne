cmake_minimum_required(VERSION 3.5)
message(STATUS "Cmake version ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

include_directories(${demo_SOURCE_DIR}/EXER2/include)
include_directories(${demo_SOURCE_DIR}/EXER2/src)

find_package(Threads)
add_executable(exe2
    ${demo_SOURCE_DIR}/EXER2/include/hashNode.hpp
    ${demo_SOURCE_DIR}/EXER2/src/hashBucket.hpp
    ${demo_SOURCE_DIR}/EXER2/src/hashMap.hpp
    ${demo_SOURCE_DIR}/EXER2/src/tests.hpp
    main2.cpp
)
target_link_libraries(exe2 ${CMAKE_THREAD_LIBS_INIT})
