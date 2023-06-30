#pragma once

#include <vector>

#include "Cube.h"

class RubiksCube
{
public:
    RubiksCube()
    {
        for (int x = -1; x <= 1; x+=1)
        {
            for (int y = -1; y <= 1; y+=1)
            {
                for (int z = -1; z <= 1; z+=1)
                {
                    Cube cube = Cube();
                    cube.translate(glm::vec3(x, y, z));
                    cube.center = glm::vec3(x, y, z);
                    cubes.push_back(cube);
                }
            }
        }
    }

    int get_next_texture_id()
    {
        current_texture_id = (current_texture_id + 1) % texture_ids.size();
        return texture_ids[current_texture_id];
    }

    void rotate_face(glm::vec3 axis, GLfloat angle)
    {
        for (int i = 0; i < cubes.size(); i++)
        {
            Cube& cube = cubes[i];
            GLfloat dot = glm::dot(cube.center, axis);
            if (dot > 0.0f)
            {
                cube.rotate(axis, angle);
            }
        }
    }

    void shuffle()
    {
        int axis = rand() % 3;
        int direction = rand() % 2;
        int angle = rand() % 3 + 1;
        if (direction == 0) angle *= -1;

        glm::vec3 rotation_axis = glm::vec3(0.0f);
        rotation_axis[axis] = angle * 1.0f;

        rotate_face(rotation_axis, angle * 90.0f);
    }

    void reset()
    {
        for (int x = -1; x <= 1; x+=1)
        {
            for (int y = -1; y <= 1; y+=1)
            {
                for (int z = -1; z <= 1; z+=1)
                {
                    int index = (x + 1) * 9 + (y + 1) * 3 + (z + 1);
                    cubes[index].reset(x, y, z);
                    cubes[index].translate(glm::vec3(x, y, z));
                }
            }
        }
    }

    std::vector<Cube> cubes;
    std::vector<int> texture_ids;
    int current_texture_id = -1;
    float opacity = 1.0f;
};

static RubiksCube rubiks_cube;