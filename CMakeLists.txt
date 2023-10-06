cmake_minimum_required(VERSION 3.0.0)
project(memory VERSION 0.1.0 LANGUAGES C CXX)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES "src/*.cpp")
add_executable(face ${SOURCES})
