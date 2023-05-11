#pragma once

#include <GL/glew.h>

#include "Structures.h"

class SkyBox
{
public:
    SkyBox()
        : vertices_position(skybox_vertices),
        vao(0),
        texture_id(-1)
    {}

    const std::vector<GLfloat>& vertices_position;
    GLuint vao;
    unsigned int texture_id;
};

static SkyBox skybox;