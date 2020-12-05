cmake_minimum_required(VERSION 3.17)
project(adventofcode)

set(CMAKE_CXX_FLAGS "-O3 -std=c++17")

file(GLOB sources RELATIVE "${PROJECT_SOURCE_DIR}/day*" "day*/day*.cpp")
foreach( source_file ${sources})
  get_filename_component(dir ${source_file} DIRECTORY)
  set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
  get_filename_component(target ${source_file} NAME_WE)
  add_executable(${target}.out ${source_file})
endforeach( source_file ${sources})
