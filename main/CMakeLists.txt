set(CMAKE_CXX_STANDARD 17) # Use C++17 or your desired standard

file(GLOB_RECURSE APP_SOURCES "src/*.c" "src/*.cpp")

idf_component_register(
    SRCS "main.cpp" ${APP_SOURCES} 
    INCLUDE_DIRS "include"
)

