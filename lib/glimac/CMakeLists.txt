cmake_minimum_required(VERSION 3.10)

add_library(glimac)

file(GLOB_RECURSE GLIMAC_SOURCES CONFIGURE_DEPENDS src/*)
if (MSVC)
target_compile_options(glimac PRIVATE /W3)
else()
target_compile_options(glimac PRIVATE -std=c++17)
endif()
target_sources(glimac PRIVATE ${GLIMAC_SOURCES})
target_include_directories(glimac PUBLIC ../glimac)
