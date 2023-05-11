#pragma once

#include <GL/glew.h>

#include <string>
#include <vector>

static const std::vector<GLfloat> cube_vertices = {

    // RIGHT FACE
     0.5, -0.5, -0.5,
     0.5,  0.5,  0.5,
     0.5, -0.5,  0.5,

     0.5,  0.5,  0.5,
     0.5, -0.5, -0.5,
     0.5,  0.5, -0.5,

    // LEFT FACE
    -0.5, -0.5, -0.5,
    -0.5, -0.5,  0.5,
    -0.5,  0.5,  0.5,

    -0.5, -0.5, -0.5,
    -0.5,  0.5,  0.5,
    -0.5,  0.5, -0.5,

    // FRONT FACE
    -0.5,  0.5,  0.5,
    -0.5, -0.5,  0.5,
     0.5, -0.5,  0.5,

     0.5,  0.5,  0.5,
    -0.5,  0.5,  0.5,
     0.5, -0.5,  0.5,

    // BACK FACE
     0.5,  0.5, -0.5,
    -0.5, -0.5, -0.5,
    -0.5,  0.5, -0.5,

     0.5,  0.5, -0.5,
     0.5, -0.5, -0.5,
    -0.5, -0.5, -0.5,

    // TOP FACE
     0.5,  0.5,  0.5,
    -0.5,  0.5, -0.5,
    -0.5,  0.5,  0.5,

     0.5,  0.5,  0.5,
     0.5,  0.5, -0.5,
    -0.5,  0.5, -0.5,

    // BOTTOM FACE
     0.5, -0.5,  0.5,
    -0.5, -0.5, -0.5,
     0.5, -0.5, -0.5,

     0.5, -0.5,  0.5,
    -0.5, -0.5,  0.5,
    -0.5, -0.5, -0.5,
};

static const std::vector<GLfloat> cube_colors = {

    // Green
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,

    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,

    // Yellow
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,

    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,

    // Orange
    1.0, 0.5, 0.0,
    1.0, 0.5, 0.0,
    1.0, 0.5, 0.0,

    1.0, 0.5, 0.0,
    1.0, 0.5, 0.0,
    1.0, 0.5, 0.0,

    // Red
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,

    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,

    // White
    1.0, 1.0, 1.0,
    1.0, 1.0, 1.0,
    1.0, 1.0, 1.0,

    1.0, 1.0, 1.0,
    1.0, 1.0, 1.0,
    1.0, 1.0, 1.0,

    // Blue
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,

    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
};

static const std::vector<GLfloat> texture_uv = {

    // Green
    0.0, 0.33333,
    0.25, 0.33333,
    0.25, 0.66666,

    0.0, 0.33333,
    0.25, 0.66666,
    0.0, 0.66666,

    // Yellow
    0.75, 0.66666,
    1.0, 0.33333,
    1.0, 0.66666,

    0.75, 0.66666,
    0.75, 0.33333,
    1.0, 0.33333,

    // Orange
    0.75, 0.33333,
    0.5, 0.66666,
    0.5, 0.33333,

    0.5, 0.66666,
    0.75, 0.33333,
    0.75, 0.66666,

    // Red
    0.25, 0.66666,
    0.25, 0.33333,
    0.5, 0.33333,

    0.5, 0.66666,
    0.25, 0.66666,
    0.5, 0.33333,

    // White
    0.5, 0.33333,
    0.25, 0.0,
    0.5, 0.0,

    0.5, 0.33333,
    0.25, 0.33333,
    0.25, 0.0,

    // Blue
    0.5, 0.66666,
    0.25, 1.0,
    0.25, 0.66666,

    0.5, 0.66666,
    0.5, 1.0,
    0.25, 1.0,
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

static const std::vector<std::string> faces = {
    "/home/david/Desktop/Image/POGL/PROJET/RubiksCubeGL/SkyboxTextures/right.jpg",
    "/home/david/Desktop/Image/POGL/PROJET/RubiksCubeGL/SkyboxTextures/left.jpg",
    "/home/david/Desktop/Image/POGL/PROJET/RubiksCubeGL/SkyboxTextures/top.jpg",
    "/home/david/Desktop/Image/POGL/PROJET/RubiksCubeGL/SkyboxTextures/bottom.jpg",
    "/home/david/Desktop/Image/POGL/PROJET/RubiksCubeGL/SkyboxTextures/front.jpg",
    "/home/david/Desktop/Image/POGL/PROJET/RubiksCubeGL/SkyboxTextures/back.jpg"
};