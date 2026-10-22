cmake_mimimum_required(VERSION 3,20)
project(CityGlaze LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)
find_package(nlohhman_json CONFIG REQUIRED)

add_executable(citglaze
    src/main.cpp
)

target_link_libraries(cityglaze PRIVATE 
    CURL::libcurl
    nlohhman_json::nlohhman_json
)