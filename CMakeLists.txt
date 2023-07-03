cmake_minimum_required(VERSION 3.22.1)
project(rubiksCubeGL)

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
configure_file(RubiksCubeTextures/1.png RubiksCubeTextures/1.png COPYONLY)
configure_file(RubiksCubeTextures/2.jpg RubiksCubeTextures/2.jpg COPYONLY)
configure_file(RubiksCubeTextures/3.png RubiksCubeTextures/3.png COPYONLY)
configure_file(RubiksCubeTextures/4.jpeg RubiksCubeTextures/4.jpeg COPYONLY)
configure_file(RubiksCubeTextures/5.jpeg RubiksCubeTextures/5.jpeg COPYONLY)
configure_file(RubiksCubeTextures/6.jpeg RubiksCubeTextures/6.jpeg COPYONLY)
configure_file(RubiksCubeTextures/7.jpeg RubiksCubeTextures/7.jpeg COPYONLY)

configure_file(SkyboxTextures/Black/back.jpg SkyboxTextures/Black/back.jpg COPYONLY)
configure_file(SkyboxTextures/Black/bottom.jpg SkyboxTextures/Black/bottom.jpg COPYONLY)
configure_file(SkyboxTextures/Black/front.jpg SkyboxTextures/Black/front.jpg COPYONLY)
configure_file(SkyboxTextures/Black/left.jpg SkyboxTextures/Black/left.jpg COPYONLY)
configure_file(SkyboxTextures/Black/right.jpg SkyboxTextures/Black/right.jpg COPYONLY)
configure_file(SkyboxTextures/Black/top.jpg SkyboxTextures/Black/top.jpg COPYONLY)

configure_file(SkyboxTextures/Sky/back.jpg SkyboxTextures/Sky/back.jpg COPYONLY)
configure_file(SkyboxTextures/Sky/bottom.jpg SkyboxTextures/Sky/bottom.jpg COPYONLY)
configure_file(SkyboxTextures/Sky/front.jpg SkyboxTextures/Sky/front.jpg COPYONLY)
configure_file(SkyboxTextures/Sky/left.jpg SkyboxTextures/Sky/left.jpg COPYONLY)
configure_file(SkyboxTextures/Sky/right.jpg SkyboxTextures/Sky/right.jpg COPYONLY)
configure_file(SkyboxTextures/Sky/top.jpg SkyboxTextures/Sky/top.jpg COPYONLY)

configure_file(SkyboxTextures/Volcano/back.png SkyboxTextures/Volcano/back.png COPYONLY)
configure_file(SkyboxTextures/Volcano/bottom.png SkyboxTextures/Volcano/bottom.png COPYONLY)
configure_file(SkyboxTextures/Volcano/front.png SkyboxTextures/Volcano/front.png COPYONLY)
configure_file(SkyboxTextures/Volcano/left.png SkyboxTextures/Volcano/left.png COPYONLY)
configure_file(SkyboxTextures/Volcano/right.png SkyboxTextures/Volcano/right.png COPYONLY)
configure_file(SkyboxTextures/Volcano/top.png SkyboxTextures/Volcano/top.png COPYONLY)

configure_file(shaders/SkyboxVS.glsl shaders/SkyboxVS.glsl COPYONLY)
configure_file(shaders/SkyboxFS.glsl shaders/SkyboxFS.glsl COPYONLY)

add_library(${PROJECT_NAME}_lib_vendor STATIC)
target_include_directories(${PROJECT_NAME}_lib_vendor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
add_subdirectory(vendor)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw GLEW::GLEW glm::glm
                      ${PROJECT_NAME}_lib_vendor)