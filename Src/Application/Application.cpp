
#include <iostream>

#include <PIIK/Platform/Windows/Console.h>
#include <PIIK/Utility/Logger.h>
#include <NativeWindow/Service/InputService/InputService.h>

#include "Application.h"
#include "Renderer/RenderCommand/RenderCommand.h"
#include "Editor/Editor.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Time/Time.h"

static void ConsoleLogCallBack(Piik::Logger::Level level, const char* tag, const char* message)
{
    using namespace Piik::Windows;

    if (level == Piik::Logger::Level::Error)
    {
        Console::SetStdOutColor(Console::Color::Red, Console::Color::Black);
        std::cout << "[E]" << tag << '\t' << message << std::endl;
        Console::SetStdOutColor(Console::Color::White, Console::Color::Black);
    }
    else if (level == Piik::Logger::Level::Warning)
    {
        Console::SetStdOutColor(Console::Color::Yellow, Console::Color::Black);
        std::cout << "[W]" << tag << '\t'  << message << std::endl;
        Console::SetStdOutColor(Console::Color::White, Console::Color::Black);
    }
    else
        std::cout << "[I]" << tag << '\t'  << message << std::endl;
}

void Application::InitWindow(RendererApi api, int windowWidth, int windowHeight)
{
    _api = api;

    Piik::Windows::Console::CreateConsole();
    Piik::Windows::Console::AttachConsole();
    Piik::Windows::Console::SetConsoleOutputUtf8();
    Piik::Logger::SetLogger(ConsoleLogCallBack);

    _pWindow = new NativeWindow::Window();
    _pWindow->Create(windowWidth, windowHeight, WINDOW_NAME, NativeWindow::WindowStyle::DefaultStyle());
    _pWindow->AddService<NativeWindow::InputService>();

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
    _pImpl->UnRegisterWindow();

    delete _pWindow;
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
    double thisFrameAtLeastElapsed = 1000 / static_cast<double>(_targetFrame);
    if (thisFrameElapsed > thisFrameAtLeastElapsed)
        return;

    // windows should not use sleep to wait
    double waitTime = thisFrameAtLeastElapsed - thisFrameElapsed;
    Helper::Timer waitTimer;
    waitTimer.SetNow();
    while (true)
    {
        double elapsed = static_cast<double>(waitTimer.GetInterval()) / 1000;
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

const Helper::ResPtr<Helper::Window::WindowHandle>& Application::GetWindowHandle()
{
    return _pImpl->GetWindowHandle();
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


