cmake_minimum_required(VERSION 3.14)
project(12 VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 14)

set(BASE_SOURCE 
        ${PROJECT_SOURCE_DIR}/generateSortTree.cpp
        ${PROJECT_SOURCE_DIR}/sort.cpp
        )
add_library(demo_static STATIC ${BASE_SOURCE})
set_target_properties(demo_static PROPERTIES 
        CLEAN_DIRECT_OUTPUT 1
        NO_SONAME 1
        CXX_VISIBILITY_PRESET hidden)
set_target_properties(demo_static PROPERTIES
        OUTPUT_NAME "demo_static")

add_executable(testcase ${PROJECT_SOURCE_DIR}/main.cpp)
target_link_libraries(testcase demo_static)

