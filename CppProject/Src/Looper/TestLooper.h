#pragma once

#include "Application/AppLooper.h"
#include "Renderer/Camera/OrthoCamera.h"
#include "Renderer/Shader/ShaderProgram.h"
#include "Renderer/Buffer/VertexArray.h"

class TestLooper : public AppLooper
{
public:
    TestLooper();
    ~TestLooper() override = default;

public:
    void RenderLoop() override;
    void EditorLoop() override;

private:
    Renderer::OrthoCamera _orthoCamera;
    Ptr<Renderer::ShaderProgram> _pShader;
    Ptr<Renderer::VertexArray> _pVertexArray;
};


