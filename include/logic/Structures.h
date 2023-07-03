#pragma once

#include <GL/glew.h>

#include <string>
#include <vector>

static const std::vector<GLfloat> cube_vertices = {

    // Red RIGHT FACE
     0.5, -0.5, -0.5,
     0.5,  0.5,  0.5,
     0.5, -0.5,  0.5,

     0.5,  0.5,  0.5,
     0.5, -0.5, -0.5,
     0.5,  0.5, -0.5,

    // Orange LEFT FACE
    -0.5, -0.5,  0.5,
    -0.5,  0.5, -0.5,
    -0.5, -0.5, -0.5,

    -0.5,  0.5, -0.5,
    -0.5, -0.5,  0.5,
    -0.5,  0.5,  0.5,

    // White TOP FACE
     0.5,  0.5,  0.5,
    -0.5,  0.5, -0.5,
    -0.5,  0.5,  0.5,

    -0.5,  0.5, -0.5,
     0.5,  0.5,  0.5,
     0.5,  0.5, -0.5,

    // Blue BOTTOM FACE
     0.5, -0.5, -0.5,
    -0.5, -0.5,  0.5,
    -0.5, -0.5, -0.5,

    -0.5, -0.5,  0.5,
     0.5, -0.5, -0.5,
     0.5, -0.5,  0.5,

    // Green FRONT FACE
     0.5, -0.5,  0.5,
    -0.5,  0.5,  0.5,
    -0.5, -0.5,  0.5,

    -0.5,  0.5,  0.5,
     0.5, -0.5,  0.5,
     0.5,  0.5,  0.5,

    // Yellow BACK FACE
    -0.5, -0.5, -0.5,
     0.5,  0.5, -0.5,
     0.5, -0.5, -0.5,

     0.5,  0.5, -0.5,
    -0.5, -0.5, -0.5,
    -0.5,  0.5, -0.5
};

static const std::vector<GLfloat> cube_colors = {

    // Red RIGHT FACE
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,

    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,

    // Orange LEFT FACE
    1.0, 0.5, 0.0,
    1.0, 0.5, 0.0,
    1.0, 0.5, 0.0,

    1.0, 0.5, 0.0,
    1.0, 0.5, 0.0,
    1.0, 0.5, 0.0,

    // White TOP FACE
    1.0, 1.0, 1.0,
    1.0, 1.0, 1.0,
    1.0, 1.0, 1.0,

    1.0, 1.0, 1.0,
    1.0, 1.0, 1.0,
    1.0, 1.0, 1.0,

    // Blue BOTTOM FACE
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,

    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,

    // Green TOP FACE
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,

    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,

    // Yellow BACK FACE
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,

    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,

};

static const std::vector<GLfloat> texture_uv = {

    // Red RIGHT FACE
    0.75, 0.33333,
    0.5, 0.66666,
    0.5, 0.33333,

    0.5, 0.66666,
    0.75, 0.33333,
    0.75, 0.66666,

    // Orange LEFT FACE
    0.25, 0.33333,
    0.0, 0.66666,
    0.0, 0.33333,

    0.0, 0.66666,
    0.25, 0.33333,
    0.25, 0.66666,

    // White TOP FACE
    0.5, 0.66666,
    0.25, 1.0,
    0.25, 0.66666,

    0.25, 1.0,
    0.5, 0.66666,
    0.5, 1.0,

    // Blue BOTTOM FACE
    0.5, 0.0,
    0.25, 0.33333,
    0.25, 0.0,

    0.25, 0.33333,
    0.5, 0.0,
    0.5, 0.33333,

    // Green TOP FACE
    0.5, 0.33333,
    0.25, 0.66666,
    0.25, 0.33333,

    0.25, 0.66666,
    0.5, 0.33333,
    0.5, 0.66666,

    // Yellow BACK FACE
    1.0, 0.33333,
    0.75, 0.66666,
    0.75, 0.33333,

    0.75, 0.66666,
    1.0, 0.33333,
    1.0, 0.66666,
};

static const std::vector<GLfloat> skybox_vertices = {
    // positions          
    -10.0,  10.0, -10.0,
    -10.0, -10.0, -10.0,
     10.0, -10.0, -10.0,
     10.0, -10.0, -10.0,
     10.0,  10.0, -10.0,
    -10.0,  10.0, -10.0,

    -10.0, -10.0,  10.0,
    -10.0, -10.0, -10.0,
    -10.0,  10.0, -10.0,
    -10.0,  10.0, -10.0,
    -10.0,  10.0,  10.0,
    -10.0, -10.0,  10.0,

     10.0, -10.0, -10.0,
     10.0, -10.0,  10.0,
     10.0,  10.0,  10.0,
     10.0,  10.0,  10.0,
     10.0,  10.0, -10.0,
     10.0, -10.0, -10.0,

    -10.0, -10.0,  10.0,
    -10.0,  10.0,  10.0,
     10.0,  10.0,  10.0,
     10.0,  10.0,  10.0,
     10.0, -10.0,  10.0,
    -10.0, -10.0,  10.0,

    -10.0,  10.0, -10.0,
     10.0,  10.0, -10.0,
     10.0,  10.0,  10.0,
     10.0,  10.0,  10.0,
    -10.0,  10.0,  10.0,
    -10.0,  10.0, -10.0,

    -10.0, -10.0, -10.0,
    -10.0, -10.0,  10.0,
     10.0, -10.0, -10.0,
     10.0, -10.0, -10.0,
    -10.0, -10.0,  10.0,
     10.0, -10.0,  10.0
};

static const std::vector<std::string> Skyfaces = {
    "SkyboxTextures/Sky/right.jpg",
    "SkyboxTextures/Sky/left.jpg",
    "SkyboxTextures/Sky/top.jpg",
    "SkyboxTextures/Sky/bottom.jpg",
    "SkyboxTextures/Sky/front.jpg",
    "SkyboxTextures/Sky/back.jpg"
};

static const std::vector<std::string> Volcanofaces = {
    "SkyboxTextures/Volcano/right.png",
    "SkyboxTextures/Volcano/left.png",
    "SkyboxTextures/Volcano/top.png",
    "SkyboxTextures/Volcano/bottom.png",
    "SkyboxTextures/Volcano/front.png",
    "SkyboxTextures/Volcano/back.png"
};

static const std::vector<std::string> Blackfaces = {
    "SkyboxTextures/Black/right.jpg",
    "SkyboxTextures/Black/left.jpg",
    "SkyboxTextures/Black/top.jpg",
    "SkyboxTextures/Black/bottom.jpg",
    "SkyboxTextures/Black/front.jpg",
    "SkyboxTextures/Black/back.jpg"
};