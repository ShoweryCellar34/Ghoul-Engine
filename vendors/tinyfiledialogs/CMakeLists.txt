set(POSITION_INDEPENDENT_CODE true)

cmake_minimum_required(VERSION 3.10)
project(tinyfiledialogs LANGUAGES C)

add_library(tinyfiledialogs STATIC tinyfiledialogs/tinyfiledialogs.c)
target_include_directories(tinyfiledialogs PUBLIC tinyfiledialogs)
