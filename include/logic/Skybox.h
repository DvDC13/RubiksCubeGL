#pragma once

#include <GL/glew.h>

#include "Structures.h"

class SkyBox
{
public:
    SkyBox()
        : vertices_position(skybox_vertices),
        vao(0),
        current_texture_id(-1)
    {}

    int get_next_texture_id()
    {
        current_texture_id = (current_texture_id + 1) % texture_ids.size();
        return texture_ids[current_texture_id];
    }

    const std::vector<GLfloat>& vertices_position;
    GLuint vao;
    unsigned int current_texture_id;
    std::vector<int> texture_ids;
};

static SkyBox skybox;