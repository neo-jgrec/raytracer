add_library(raytracer_plane SHARED)

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

target_sources(raytracer_plane
        PRIVATE
        ${SOURCES}
)

target_include_directories(raytracer_plane
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/includes
)

set_target_properties(raytracer_plane PROPERTIES PREFIX "")

install(TARGETS raytracer_plane LIBRARY DESTINATION lib)
