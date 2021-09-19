cmake_minimum_required(VERSION 3.15)

project(GravSim VERSION 1.0)

add_executable(gravsim)

add_subdirectory(vendor/imgui)
target_include_directories(gravsim PUBLIC vendor/imgui)

add_subdirectory(vendor/imgui-sfml)
target_include_directories(gravsim PUBLIC vendor/imgui-sfml)

add_subdirectory(src)
target_link_libraries(gravsim PUBLIC sfml-graphics sfml-window sfml-system OpenGL)