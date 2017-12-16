cmake_minimum_required(VERSION 3.9)
project(FileSystem)

set(CMAKE_CXX_STANDARD 11)

add_executable(FileSystem main.cpp structHeader.h command.h command.cpp init.h init.cpp load.h load.cpp filecommand.h filecommand.cpp commonfunc.h commonfunc.cpp)
add_executable(main main.cpp)
add_executable(starter main.cpp)
set_target_properties(starter PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")