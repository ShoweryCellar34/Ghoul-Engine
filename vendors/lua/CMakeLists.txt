set(POSITION_INDEPENDENT_CODE true)

cmake_minimum_required(VERSION 3.10)
project(lua LANGUAGES C)

file(GLOB lua_source lua/*.c)
add_library(lua STATIC ${lua_source})
target_include_directories(lua PUBLIC lua)
