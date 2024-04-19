add_library(raytracer_sfml SHARED)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

target_sources(raytracer_sfml
    PRIVATE
        ${SOURCES}
)

target_include_directories(raytracer_sfml
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/includes
)

find_package(SFML COMPONENTS graphics REQUIRED)

target_link_libraries(raytracer
    PRIVATE
        sfml-graphics
)

set_target_properties(raytracer_sfml PROPERTIES PREFIX "")

install(TARGETS raytracer_sfml LIBRARY DESTINATION lib)
