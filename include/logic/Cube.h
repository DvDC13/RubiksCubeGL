#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

#include "Structures.h"

#define DURATION 400.0f

static std::chrono::time_point<std::chrono::system_clock> start_time;

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

    void rotate(glm::vec3 axis, GLfloat angle)
    {
        rotating = true;
        m_angle = angle;
        m_axis = axis;
    }

    glm::mat4 get_model()
    {
        if (!rotating) return model;

        elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time).count();
        if (elapsed_time >= DURATION)
        {
            rotating = false;
            elapsed_time = 0.0f;
            model = glm::rotate(glm::mat4(1.0f), glm::radians(m_angle), m_axis) * model;
            return model;
        }

        float angle = m_angle * (elapsed_time / DURATION);

        glm::mat4 new_model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_axis) * model;
        return new_model;
    }

    glm::mat4 model;
    const std::vector<GLfloat>& vertices_position;
    const std::vector<GLfloat>& colors;
    const std::vector<GLfloat>& texture_coords;
    GLuint vao;

    float elapsed_time = 0.0f;
    bool rotating = false;

    float m_angle = 0.0f;
    glm::vec3 m_axis;
};