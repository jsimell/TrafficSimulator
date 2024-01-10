cmake_minimum_required(VERSION 3.11.0)
project(traffic_simulator VERSION 0.1.0)

enable_language(CXX)

# Check if the operating system is Windows
if(WIN32)
    message(FATAL_ERROR "Windows is not supported. Please build this project on MacOS or Linux.")
endif()

# use C++ standard version 17
set(CMAKE_CXX_STANDARD 17)
# produce non-optimized code with debug symbols
set(CMAKE_BUILD_TYPE Debug)

message(STATUS "BUILD directory is ${CMAKE_BINARY_DIR}")
message(STATUS "SRC directory is ${CMAKE_SOURCE_DIR}")

# Add all .c, - files under src/ directory
file(GLOB SOURCES_C "src/*.c")
# Add all .cpp, - files under src/ directory
file(GLOB SOURCES_CPP "src/*.cpp")
# Add all .hpp, - files under src/ directory
file(GLOB SOURCES_HPP "src/*.hpp")
# Add all .h, - files under src/ directory
file(GLOB SOURCES_H "src/*.h")
set(SOURCES ${SOURCES_C} ${SOURCES_CPP} ${SOURCES_H} ${SOURCES_HPP})
message(STATUS "SRC directory source code files: \n\t-- HEADERS: ${SOURCES_H}${SOURCES_HPP}\n\t-- C SOURCES: ${SOURCES_C}\n\t-- CPP SOURCE:${SOURCES_CPP}\n\t-- ALL:${SOURCES}")

# add the executable target
add_executable(main)

target_sources(main PUBLIC ${SOURCES})
target_include_directories(main PUBLIC .)
target_include_directories(main PUBLIC src)

# Set SFML directory based on the operating system
if(APPLE)
    # macOS
    set(SFML_DIR ${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1-macOS/lib)
elseif(UNIX AND NOT APPLE)
    # Linux
    set(SFML_DIR ${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1-linux/lib/cmake/SFML)
endif()

find_package(SFML 2.6 COMPONENTS graphics REQUIRED)
target_link_libraries(main sfml-graphics)

# get a lot of warnings
if(MSVC)
    target_compile_options(main PRIVATE /Wall)
else()
    # gcc and clang
    target_compile_options(main PRIVATE -Wall -Wextra -pedantic -Wno-missing-field-initializers)
endif()