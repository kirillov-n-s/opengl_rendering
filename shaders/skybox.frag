#version 460 core

in vec3 TexCoord;

out vec4 FragColor;

uniform samplerCube uTexture;

void main()
{
    FragColor = texture(uTexture, TexCoord);
}