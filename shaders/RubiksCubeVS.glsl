#version 460

in vec3 position;
in vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vColor;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    vColor = color;
}