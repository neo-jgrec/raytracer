cmake_minimum_required(VERSION 3.20)
project(imgui)

include_directories(${CMAKE_SOURCE_DIR}/libs/imgui)

file(GLOB IMGUI_SRC
	${CMAKE_SOURCE_DIR}/libs/imgui/*.cpp
)

add_library(imgui SHARED ${IMGUI_SRC})
target_link_libraries(imgui)
