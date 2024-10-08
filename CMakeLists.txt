cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_VERBOSE_MAKEFILE ON)


# Project name
project(cryptopals)

find_package(OpenSSL REQUIRED)
if (NOT OPENSSL_FOUND)
    message(FATAL_ERROR "OpenSSL not found!")
endif()

include_directories("${OPENSSL_INCLUDE_DIR}")
link_libraries("${OPENSSL_LIBRARIES}")

# Set the C standard
set(CMAKE_C_STANDARD 11)

file(GLOB LIB_SOURCES "${CMAKE_SOURCE_DIR}/src/lib/*.c")
add_library(handroll SHARED ${LIB_SOURCES})

target_compile_options(handroll PRIVATE -ggdb -Wall)

# Specify the include directories for the library
target_include_directories(handroll PUBLIC "${CMAKE_SOURCE_DIR}/src/lib")

# Specify the output directories for the library and binaries
set_target_properties(handroll PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/lib"
)

file(GLOB BIN_SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")

# Create an executable for each .c file in the bin directory
foreach(BIN_SRC ${BIN_SOURCES})
    get_filename_component(BIN_NAME ${BIN_SRC} NAME_WE)
    add_executable(${BIN_NAME} ${BIN_SRC})
    target_link_libraries(${BIN_NAME} PRIVATE handroll)
    set_target_properties(${BIN_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
    )
    target_compile_options(${BIN_NAME} PRIVATE -Wall)

endforeach()


