cmake_minimum_required(VERSION 3.13)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

project(DataExchanger)

find_package(OpenCasCade REQUIRED)

add_executable(StepToStl StepToStl.cpp)

target_include_directories(StepToStl PUBLIC ${OCC_INCLUDE_DIR})
target_link_libraries(StepToStl PUBLIC ${OCC_LIBRARIES})