add_library(raytracer_cone SHARED)

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

target_sources(raytracer_cone
        PRIVATE
        ${SOURCES}
)

target_include_directories(raytracer_cone
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/includes
)

set_target_properties(raytracer_cone PROPERTIES PREFIX "")

install(TARGETS raytracer_cone LIBRARY DESTINATION lib)
