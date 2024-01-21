
layout (std140, binding = 8) uniform MaterialProperty
{
    vec3 u_CameraPosition;
    vec3 u_SelfColor;
    float u_SpecularShininess;
};