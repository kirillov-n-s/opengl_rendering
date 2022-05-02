#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexcoord;

out vec3 Position;
out vec3 Normal;

uniform mat4 uModel;
uniform mat4 uNormalModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
    Position = vec3(uModel * vec4(aPosition, 1.0));
    Normal = mat3(uNormalModel) * aNormal;
}
