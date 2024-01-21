
layout (std140, binding = 0) uniform MvpMatrices
{
    mat4 u_ModelMatrix;
    mat4 u_ViewMatrix;
    mat4 u_ProjectionMatrix;
};