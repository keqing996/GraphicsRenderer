#pragma once

#include "Component.h"
#include "Scene/Light/Light.h"

class CompCamera: public ComponentWithType<ComponentType::Light>
{
public:


private:
    Ptr<Light> _pLight;

};