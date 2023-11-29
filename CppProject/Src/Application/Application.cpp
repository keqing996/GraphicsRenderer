
#include "Application.h"
#include "Util/Logger/Logger.h"
#include "Renderer/RenderCommand/RenderCommand.h"
#include "Editor/Editor.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Time/Time.h"

void Application::InitWindow(RendererApi api, int windowWidth, int windowHeight)
{
    _api = api;

    _width = windowWidth;
    _height = windowHeight;

    Util::Logger::InitConsoleLogger();

#ifdef BUILD_RELEASE
    Util::Logger::InitFileLogger("./log.txt");
    Util::Logger::SetFilterLevel(Util::Logger::Level::Error);
#endif

    _pImpl = new ApplicationWinImp();
    _pImpl->RegisterAndCreateWindow(_width, _height, WINDOW_NAME);
    _pImpl->ShowWindow();

    Renderer::RenderCommand::Init();
    Editor::Environment::Init();
    Time::Init();
}

void Application::DestroyWindow()
{
    for (auto pLooper : _loopLogic)
        delete pLooper;

    Editor::Environment::Destroy();
    Renderer::RenderCommand::Destroy();

    _pImpl->DestroyWindow();

    delete _pImpl;
}

void Application::RunLoop()
{
    while (true)
    {
        /* Windows message loop */
        MSG msg;
        bool shouldStop = false;
        while (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                shouldStop = true;
                break;
            }

            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }

        if (shouldStop)
            break;

        UpdateTime();
        UpdateInput();
        UpdateRender();

        WaitForTargetFrame();

        _frameCount++;
    }
}

void Application::UpdateTime()
{
    Time::Update();
}

void Application::UpdateInput()
{
    Input::Mouse::ProcessEvent();
    Input::Keyboard::ProcessEvent();
}

void Application::UpdateRender()
{
    Renderer::RenderCommand::ClearColor(Eigen::Vector4f{0.2f, 0.2f, 0.2f, 1.0f});

    // Render Loop
    for (auto& looper : _loopLogic)
        looper->RenderLoop();

    // Editor Loop
    Editor::Environment::BeforeLoop();

    for (auto& looper : _loopLogic)
        looper->EditorLoop();

    Editor::Environment::AfterLoop();

    // Swap Buffer
    Renderer::RenderCommand::SwapBuffer();
}

void Application::WaitForTargetFrame()
{
    double thisFrameElapsed = Time::GetFrameTimerElapsed() / 1000;
    double thisFrameAtLeastElapsed = 1000 / (double)_targetFrame;
    if (thisFrameElapsed > thisFrameAtLeastElapsed)
        return;

    // windows should not use sleep to wait
    double waitTime = thisFrameAtLeastElapsed - thisFrameElapsed;
    Util::Timer waitTimer;
    waitTimer.SetNow();
    while (true)
    {
        double elapsed = (double)waitTimer.GetInterval() / 1000;
        if (elapsed > waitTime)
            break;
    }
}

int Application::GetWindowHeight()
{
    return _width;
}

int Application::GetWindowWidth()
{
    return _height;
}

RendererApi Application::GetRenderApi()
{
    return _api;
}

void* Application::GetWindowHandle()
{
    return reinterpret_cast<void*>(_pImpl->GetWindowHandle());
}

uint64_t Application::GetFrameCount()
{
    return _frameCount;
}

void Application::SetTargetFrame(uint32_t targetFrame)
{
    if (targetFrame < 30)
        targetFrame = 30;

    _targetFrame = targetFrame;
}

uint32_t Application::GetTargetFrame()
{
    return _targetFrame;
}


