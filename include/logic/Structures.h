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

static const std::vector<std::string> faces = {
    "/home/david/Desktop/Image/POGL/PROJET/RubiksCubeGL/SkyboxTextures/right.jpg",
    "/home/david/Desktop/Image/POGL/PROJET/RubiksCubeGL/SkyboxTextures/left.jpg",
    "/home/david/Desktop/Image/POGL/PROJET/RubiksCubeGL/SkyboxTextures/top.jpg",
    "/home/david/Desktop/Image/POGL/PROJET/RubiksCubeGL/SkyboxTextures/bottom.jpg",
    "/home/david/Desktop/Image/POGL/PROJET/RubiksCubeGL/SkyboxTextures/front.jpg",
    "/home/david/Desktop/Image/POGL/PROJET/RubiksCubeGL/SkyboxTextures/back.jpg"
};