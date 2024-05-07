add_library(raytracer_ambientlight SHARED)

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

target_sources(raytracer_ambientlight
        PRIVATE
        ${SOURCES}
)

target_include_directories(raytracer_ambientlight
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/includes
)

set_target_properties(raytracer_ambientlight PROPERTIES PREFIX "")

install(TARGETS raytracer_ambientlight LIBRARY DESTINATION lib)
