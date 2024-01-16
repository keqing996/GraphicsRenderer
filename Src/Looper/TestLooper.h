#pragma once

#include "Application/AppLooper.h"
#include "Renderer/InputAssemble/InputAssemble.h"
#include "Renderer/Pipeline/RendererPipeline.h"
#include "Scene/Scene.h"

class TestLooper : public AppLooper
{
public:
    TestLooper();
    ~TestLooper() override = default;

public:
    void RenderLoop() override;
    void EditorLoop() override;

private:
    Scene _scene;
    Ptr<Renderer::RendererPipeline> _pRendererPipeline;
};


