#pragma once

#include <memory>
#include <vector>
#include <NativeWindow/Window.h>
#include <PIIK/Utility/NonCopyable.h>
#include "Define/RendererApi.h"
#include "AppLooper.h"

class Application : public Piik::NonCopyable
{
public:
    static void InitWindow(RendererApi api, int windowWidth, int windowHeight);
    static void DestroyWindow();
    static void RunLoop();

    template<AppLooperImpl T, class... Types>
    static void AddLooper(Types&&... Args)
    {
        AppLooper* pLooper = new T(std::forward<Types&&...>(Args...));
        _loopLogic.push_back(pLooper);
    }

    template<AppLooperImpl T>
    static void AddLooper()
    {
        AppLooper* pLooper = new T();
        _loopLogic.push_back(pLooper);
    }

    static int GetWindowHeight();
    static int GetWindowWidth();
    static RendererApi GetRenderApi();
    static const Helper::ResPtr<Helper::Window::WindowHandle>& GetWindowHandle();
    static uint64_t GetFrameCount();
    static void SetTargetFrame(uint32_t targetFrame);
    static uint32_t GetTargetFrame();

private:
    static void UpdateTime();
    static void UpdateInput();
    static void UpdateRender();
    static void WaitForTargetFrame();

private:
    Application() = default;

private:
    /* Imp */
    inline static NativeWindow::Window* _pWindow = nullptr;

    /* Rhi */
    inline static RendererApi _api = RendererApi::OpenGL;

    /* Basic */
    inline static uint64_t _frameCount = 0;
    inline static uint32_t _targetFrame = 9999;

    /* Looper */
    inline static std::vector<AppLooper*> _loopLogic {};

    /* Const */
    static constexpr const char* WINDOW_NAME = "Graphic Render";

};