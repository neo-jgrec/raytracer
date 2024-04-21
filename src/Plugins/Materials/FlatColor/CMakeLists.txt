add_library(raytracer_flatcolor SHARED)

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

target_sources(raytracer_flatcolor
        PRIVATE
        ${SOURCES}
)

target_include_directories(raytracer_flatcolor
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/includes
)

set_target_properties(raytracer_flatcolor PROPERTIES PREFIX "")

install(TARGETS raytracer_flatcolor LIBRARY DESTINATION lib)
