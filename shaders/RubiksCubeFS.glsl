#version 460

in vec2 vTexture_uv;

uniform sampler2D tex;
uniform float opacity;

out vec4 FragColor;

void main()
{
    vec4 texColor = texture(tex, vTexture_uv);
    FragColor = vec4(texColor.rgb, opacity);
}