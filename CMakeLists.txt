cmake_minimum_required(VERSION 3.26)
project(Ground)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


if(NOT MSVC)
  set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
else()
  set(CMAKE_CXX_FLAGS_RELEASE "/O2 /Ot")
endif()

file(GLOB_RECURSE ALL_SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.hpp"
)

find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

add_library(glad STATIC
    "${PROJECT_SOURCE_DIR}/external/glad/src/glad.c"
)
target_include_directories(glad PUBLIC "${PROJECT_SOURCE_DIR}/external/glad/include")

add_executable(${PROJECT_NAME} ${ALL_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Vulkan::Vulkan
    OpenGL::GL
    glfw
    glad
    ${CMAKE_DL_LIBS}
)

if(NOT WIN32)
  target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
endif()
