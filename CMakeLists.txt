cmake_minimum_required(VERSION 3.0.0)
project(EntryPoint VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/lib/include)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(EntryPoint
        src/main.cpp
        src/glad.c
        src/stb_image.cpp
        src/Shader.cpp
        src/ShaderProgram.cpp
        src/Camera.cpp
        src/Cube.cpp
        src/Texture.cpp
        src/Scene.cpp
        src/Light.cpp)

set_property(TARGET EntryPoint PROPERTY CXX_STANDARD 17)

if (MSVC)
    target_compile_options(EntryPoint PRIVATE /W4 /EHa)
else ()
    target_compile_options(EntryPoint PRIVATE -Wall -Wextra -Wpedantic -Werror -fexceptions)
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    find_library(GLFW glfw3dll ${PROJECT_SOURCE_DIR}/lib/Release)
elseif (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    find_library(GLFW glfw3dll ${PROJECT_SOURCE_DIR}/lib/Debug)
endif ()

target_link_libraries(EntryPoint ${GLFW})

add_custom_command(TARGET EntryPoint POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/lib/$<CONFIGURATION>"
        $<TARGET_FILE_DIR:EntryPoint>)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
