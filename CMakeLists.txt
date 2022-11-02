cmake_minimum_required(VERSION 3.18)

# Set the project name
project(blackbox-analyser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./out)

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW Build documentation" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW build documentation" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW build documentation" FORCE)

add_subdirectory(libs/glfw)

# spdlog
add_subdirectory(libs/spdlog)

# Off by default
option(TEST "Build tests" OFF)
option(DEBUG_LOG "Enable debug logging" ON)

if (DEBUG_LOG)
	add_compile_definitions(BX_LOG_DEBUG)
endif()

set(TARGET_SOURCES src/main.cpp
				   src/window.cpp
				   libs/glad/src/glad.c
				   libs/imgui/imgui.cpp
				   libs/imgui/imgui_demo.cpp
                   libs/imgui/imgui_draw.cpp
                   libs/imgui/imgui_tables.cpp
                   libs/imgui/imgui_widgets.cpp
                   libs/imgui/backends/imgui_impl_glfw.cpp
                   libs/imgui/backends/imgui_impl_opengl3.cpp)

include_directories(include/
					libs/glad/include
					libs/glfw/include
					libs/imgui
					libs/imgui/backends)

add_executable(${PROJECT_NAME} ${TARGET_SOURCES})

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} spdlog::spdlog)