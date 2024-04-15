add_library(raytracer_parsing SHARED)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

target_sources(raytracer_parsing
    PRIVATE
        ${SOURCES}
)

target_include_directories(raytracer_parsing
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/includes
)

set_target_properties(raytracer_parsing PROPERTIES PREFIX "")

install(TARGETS raytracer_parsing LIBRARY DESTINATION lib)
