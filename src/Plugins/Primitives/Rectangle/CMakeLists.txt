add_library(raytracer_rectangle SHARED)

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

target_sources(raytracer_rectangle
        PRIVATE
        ${SOURCES}
)

target_include_directories(raytracer_rectangle
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/includes
)

set_target_properties(raytracer_rectangle PROPERTIES PREFIX "")

install(TARGETS raytracer_rectangle LIBRARY DESTINATION lib)
