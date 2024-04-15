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

install(TARGETS raytracer)
