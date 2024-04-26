cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(raytracer)

# Set the default C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# Use pthreads if possible
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads)

if(CMAKE_USE_PTHREADS_INIT)
	set(CMAKE_THREAD_LIBS_INIT "pthread")
endif()

# Disable developer warnings for CMake
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")

# Add our local modules to the path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")

# The default name of the generated component
set(CMAKE_INSTALL_DEFAULT_COMPONENT_NAME "default")

# Export all the compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# If ccache is installed, use to speed up the build
find_program(CCACHE_FOUND ccache HINTS /bin /usr/bin)
if(CCACHE_FOUND)
	set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
	set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif()

# Set compilation flags
add_compile_options(-Wall
	-Wextra
	-pedantic-errors
	-fexceptions
	-ffunction-sections
	-fdata-sections
	-fasynchronous-unwind-tables
	-fno-delete-null-pointer-checks
	-fno-common
	-fno-omit-frame-pointer
	-fno-strict-aliasing
	-fno-semantic-interposition
	-fstack-protector-strong
	-fstack-clash-protection
	-flto=auto
	-fdiagnostics-color=auto
	-grecord-gcc-switches
	-pipe
	-pthread
)

# If in debug mode, enable debug flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_compile_options(-O0 -g3 -DDEBUG)
endif()

# Enable glibc assertions
add_definitions(-D_GLIBCXX_ASSERTIONS)

# Enable fortify by default
if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 12)
	# GCC 12 supports automatically initializing variables to zero
	add_compile_options(-ftrivial-auto-var-init=zero -O)

	# First we need to undef _FORTIFY_SOURCE as some systems
	# or libraries might have it set it previously.
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=3 ")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=3 ")
else()
	add_definitions(-D_FORTIFY_SOURCE=2)
endif()

find_package(Doxygen)
if (DOXYGEN_FOUND)
  set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/docs/Doxyfile.in)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
  message("Doxygen build started")

  add_custom_target(doc_doxygen
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND cp -r ${CMAKE_SOURCE_DIR}/assets.tek ${CMAKE_CURRENT_BINARY_DIR}/doc_doxygen/doxygen.html.out
    COMMAND xdg-open http://localhost:8000
    COMMAND python3 -m http.server --directory ${CMAKE_CURRENT_BINARY_DIR}/doc_doxygen/doxygen.html.out 8000
    VERBATIM
  )
  add_custom_target(doc_doxygen_action
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND cp -r ${CMAKE_SOURCE_DIR}/assets.tek ${CMAKE_CURRENT_BINARY_DIR}/doc_doxygen/doxygen.html.out
    VERBATIM
  )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

option(_SKIP_SRC "Option to skip the src directory" OFF) # OFF by default

if(NOT _SKIP_SRC)
	add_subdirectory(libs/cmake/imgui)
	add_subdirectory(libs/cmake/imgui-sfml)
    add_subdirectory(src)
endif()
