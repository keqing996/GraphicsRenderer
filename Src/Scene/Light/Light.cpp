#include "Light.h"

Light::Light(LightType type)
    : _type(type)
{
}

LightType Light::GetLightType() const
{
    return _type;
}
