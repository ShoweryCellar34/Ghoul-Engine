set(POSITION_INDEPENDENT_CODE true)

cmake_minimum_required(VERSION 3.10)
project(tinyfiledialogs LANGUAGES CXX C HOMEPAGE_URL "git clone http://git.code.sf.net/p/tinyfiledialogs/code")

add_library(tinyfiledialogs STATIC tinyfiledialogs/tinyfiledialogs.c)
target_include_directories(tinyfiledialogs PUBLIC tinyfiledialogs/)
