add_library(raytracer_parsing SHARED)

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
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

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG REQUIRED libconfig++)

target_include_directories(raytracer_parsing
        PRIVATE
        ${LIBCONFIG_INCLUDE_DIRS}
)

target_link_libraries(raytracer_parsing
        PRIVATE
        ${LIBCONFIG_LIBRARIES}
)

set_target_properties(raytracer_parsing PROPERTIES PREFIX "")

install(TARGETS raytracer_parsing LIBRARY DESTINATION lib)
