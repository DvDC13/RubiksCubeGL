cmake_minimum_required(VERSION 3.22.1)
project(RubiksCubeGL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

include_directories(${PROJECT_SOURCE_DIR}/include
                    ${PROJECT_SOURCE_DIR}/include/logic
                    ${PROJECT_SOURCE_DIR}/include/utils
                    ${PROJECT_SOURCE_DIR}/vendor)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

# Copy shader files to build directory
configure_file(shaders/RubiksCubeVS.glsl shaders/RubiksCubeVS.glsl COPYONLY)
configure_file(shaders/RubiksCubeFS.glsl shaders/RubiksCubeFS.glsl COPYONLY)

configure_file(shaders/SkyboxVS.glsl shaders/SkyboxVS.glsl COPYONLY)
configure_file(shaders/SkyboxFS.glsl shaders/SkyboxFS.glsl COPYONLY)

add_library(${PROJECT_NAME}_lib_vendor STATIC)
target_include_directories(${PROJECT_NAME}_lib_vendor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
add_subdirectory(vendor)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw GLEW::GLEW glm::glm
                      ${PROJECT_NAME}_lib_vendor)