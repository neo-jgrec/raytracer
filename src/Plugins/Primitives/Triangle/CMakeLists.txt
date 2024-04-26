add_library(raytracer_triangle SHARED)

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

target_sources(raytracer_triangle
        PRIVATE
        ${SOURCES}
)

target_include_directories(raytracer_triangle
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/includes
)

set_target_properties(raytracer_triangle PROPERTIES PREFIX "")

install(TARGETS raytracer_triangle LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/plugins)
