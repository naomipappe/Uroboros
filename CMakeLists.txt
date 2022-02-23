cmake_minimum_required(VERSION 3.0.0)
project(Ouroboros VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/lib/include)
include_directories(${PROJECT_SOURCE_DIR}/include)

# TODO separate the files into respective sub-projects for a clean structure
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/glad.c
        src/stb_image.cpp
        src/shader.cpp
        src/shaderprogram.cpp
        src/camera.cpp
        src/texture.cpp
        src/scene.cpp
        src/light.cpp
        src/mesh.cpp 
        src/model.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /EHa)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror -fexceptions)
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    find_library(GLFW glfw3dll ${PROJECT_SOURCE_DIR}/lib/Release)
elseif (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    find_library(GLFW glfw3dll ${PROJECT_SOURCE_DIR}/lib/Debug)
endif ()

target_link_libraries(${PROJECT_NAME} ${GLFW})

if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    find_library(ASSIMP assimp-vc142-mt ${PROJECT_SOURCE_DIR}/lib/Release)
elseif (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    find_library(ASSIMP assimp-vc142-mtd ${PROJECT_SOURCE_DIR}/lib/Debug)
endif ()

target_link_libraries(${PROJECT_NAME} ${ASSIMP})


add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/lib/$<CONFIGURATION>"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
