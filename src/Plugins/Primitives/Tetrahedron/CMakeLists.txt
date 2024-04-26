add_library(raytracer_tetrahedron SHARED)

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

target_sources(raytracer_tetrahedron
        PRIVATE
        ${SOURCES}
)

target_include_directories(raytracer_tetrahedron
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/includes
)

set_target_properties(raytracer_tetrahedron PROPERTIES PREFIX "")

install(TARGETS raytracer_tetrahedron LIBRARY DESTINATION lib)
