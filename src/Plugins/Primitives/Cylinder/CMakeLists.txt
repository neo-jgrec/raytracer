add_library(raytracer_cylinder SHARED)

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

target_sources(raytracer_cylinder
        PRIVATE
        ${SOURCES}
)

target_include_directories(raytracer_cylinder
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/includes
)

set_target_properties(raytracer_cylinder PROPERTIES PREFIX "")

install(TARGETS raytracer_cylinder LIBRARY DESTINATION lib)
