#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Structures.h"

class Cube
{
public:
    Cube()
        : model(glm::mat4(1.0f)),
        vertices_position(cube_vertices),
        colors(cube_colors),
        texture_coords(texture_uv),
        vao(0)
    {}

    void translate(glm::vec3 translation)
    {
        model = glm::translate(model, translation);
    }

    glm::mat4 model;
    const std::vector<GLfloat>& vertices_position;
    const std::vector<GLfloat>& colors;
    const std::vector<GLfloat>& texture_coords;
    GLuint vao;
};