add_library(raytracer_directionallight SHARED)

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

target_sources(raytracer_directionallight
        PRIVATE
        ${SOURCES}
)

target_include_directories(raytracer_directionallight
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/includes
)

set_target_properties(raytracer_directionallight PROPERTIES PREFIX "")

install(TARGETS raytracer_directionallight LIBRARY DESTINATION lib)
