add_executable(raytracer)

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
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

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG REQUIRED libconfig++)

target_include_directories(raytracer
        PRIVATE
        ${LIBCONFIG_INCLUDE_DIRS}
)

target_link_libraries(raytracer
        PRIVATE
        ${LIBCONFIG_LIBRARIES}
)

install(TARGETS raytracer)
