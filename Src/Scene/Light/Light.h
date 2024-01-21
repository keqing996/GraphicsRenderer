#pragma once

#include "LightType.h"

class Light
{
public:
    explicit Light(LightType type);

public:
    LightType GetLightType() const;

private:
    LightType _type;
};