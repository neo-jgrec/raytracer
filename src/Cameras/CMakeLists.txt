add_library(raytracer_camera SHARED)

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

target_sources(raytracer_camera
        PRIVATE
        ${SOURCES}
)

target_include_directories(raytracer_camera
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/includes
)

set_target_properties(raytracer_camera PROPERTIES PREFIX "")

install(TARGETS raytracer_camera LIBRARY DESTINATION lib)
