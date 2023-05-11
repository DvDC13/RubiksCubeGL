#version 460

in vec3 position;
in vec2 texture_uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 vTexture_uv;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    vTexture_uv = texture_uv;
}