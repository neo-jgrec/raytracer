add_executable(raytracer)

file(GLOB_RECURSE SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

target_sources(raytracer
  PRIVATE
    ${SOURCES}
)

target_include_directories(raytracer
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/includes
)

find_package(SFML COMPONENTS graphics REQUIRED)

target_link_libraries(raytracer
    PRIVATE
        sfml-graphics
)

install(TARGETS raytracer)
