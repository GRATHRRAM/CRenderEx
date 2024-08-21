cmake_minimum_required(VERSION 3.30)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(CRender_project VERSION 1.0) 

add_compile_options(-Wall -Wextra -O2)

if(CMAKE_ARGV0 STREQUAL "shared")
    add_library(CRenderEx SHARED src/CRenderEx.c)
    add_library(CRInput   SHARED src/CRInput.c)
else() 
    add_library(CRenderEx STATIC src/CRenderEx.c)
    add_library(CRInput   STATIC src/CRInput.c)
endif()

add_executable(exemple1 exemples/exemple1.c)

target_link_libraries(exemple1 PRIVATE -L. m CRenderEx CRInput)

