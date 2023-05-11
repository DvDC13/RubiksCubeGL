#version 460

in vec2 vTexture_uv;

uniform sampler2D tex;

out vec4 FragColor;

void main()
{
    FragColor = texture(tex, vTexture_uv);
}