add_library(raytracer_sphere SHARED)

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

target_sources(raytracer_sphere
        PRIVATE
        ${SOURCES}
)

target_include_directories(raytracer_sphere
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/includes
)

set_target_properties(raytracer_sphere PROPERTIES PREFIX "")

install(TARGETS raytracer_sphere LIBRARY DESTINATION lib)
