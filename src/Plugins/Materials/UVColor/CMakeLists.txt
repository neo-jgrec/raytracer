add_library(raytracer_uvcolor SHARED)

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

target_sources(raytracer_uvcolor
        PRIVATE
        ${SOURCES}
)

target_include_directories(raytracer_uvcolor
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/includes
)

set_target_properties(raytracer_uvcolor PROPERTIES PREFIX "")

install(TARGETS raytracer_uvcolor LIBRARY DESTINATION lib)
