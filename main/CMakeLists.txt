cmake_minimum_required(VERSION 3.24)

file(GLOB_RECURSE APP_SOURCES "src/*.c" "src/*.cpp")

idf_component_register(
    SRCS "main.cpp" ${APP_SOURCES} 
    INCLUDE_DIRS "include"
)

