add_library(raytracer_pointlight SHARED)

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

target_sources(raytracer_pointlight
        PRIVATE
        ${SOURCES}
)

target_include_directories(raytracer_pointlight
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/includes
)

set_target_properties(raytracer_pointlight PROPERTIES PREFIX "")

install(TARGETS raytracer_pointlight LIBRARY DESTINATION lib)
