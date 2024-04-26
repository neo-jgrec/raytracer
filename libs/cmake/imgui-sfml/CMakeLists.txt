cmake_minimum_required(VERSION 3.20)
project(imgui-sfml)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include_directories(${CMAKE_SOURCE_DIR}/libs/imgui-sfml)
include_directories(${CMAKE_SOURCE_DIR}/libs/imgui)

file(GLOB IMGUI_SFML_SRC
	${CMAKE_SOURCE_DIR}/libs/imgui-sfml/*.cpp
)

add_library(imgui-sfml SHARED ${IMGUI_SFML_SRC})
target_link_libraries(imgui-sfml imgui)