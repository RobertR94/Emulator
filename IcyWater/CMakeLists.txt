cmake_minimum_required(VERSION 3.0.0)
project(IcyWater VERSION 0.1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file( GLOB SOURCES "src/*.cpp" )
add_executable(${PROJECT_NAME} ${SOURCES})