cmake_minimum_required(VERSION 3.28)
project(moddingapi_cmake)

# set wherever you want your dll to be copied to
set(MOD_OUTPUT_DIR "E:\\Games\\NARUTO X BORUTO Ultimate Ninja STORM CONNECTIONS\\moddingapi\\mods\\base_game")

if(NOT DEFINED MOD_OUTPUT_DIR)
    message(FATAL_ERROR "MOD_OUTPUT_DIR is not defined")
endif()

# Set the static runtime library for MSVC
if (!MSVC)
    message(FATAL_ERROR "This project is only supported on MSVC")
endif()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_CXX_STANDARD 11)

#add_subdirectory(external/minhook)

# minhook gets compiled as part of the project, since idfk moddingapi doesnt like it statically linked
file(GLOB_RECURSE MH "external/minhook/src/*.c" "external/minhook/src/*.h")

add_library(moddingapi_cmake SHARED src/plugin.cpp ${MH}
        src/log.h
        src/mem.h)

target_include_directories(moddingapi_cmake PRIVATE "src" "external/minhook/include")
target_link_libraries(moddingapi_cmake PRIVATE)

# after building the project, copy the dll to the game directory and print a message
add_custom_command(TARGET moddingapi_cmake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:moddingapi_cmake> ${MOD_OUTPUT_DIR}
        COMMAND ${CMAKE_COMMAND} -E echo "Copied $<TARGET_FILE:moddingapi_cmake> to ${MOD_OUTPUT_DIR}")