#version 430 core

#include "../Library/Uniform-0-MvpMatrices.glsl"

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

layout (location = 0) out vec2 v_TexCoord;
layout (location = 1) out vec3 v_Normal;

void main()
{
    v_TexCoord = a_TexCoord;
    v_Normal = a_Normal;
    gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
}
