#include "ApplicationWinImp.h"

ApplicationWinImp::ApplicationWinImp()
{
}

void ApplicationWinImp::RegisterWin32Window()
{
    Helper::Window::RegisterInfo registerInfo {};
    registerInfo.pIcon = nullptr;
    registerInfo.pIconSmall = nullptr;
    registerInfo.pCursor = nullptr;
    registerInfo.pWinMsgProc = reinterpret_cast<void*>(&HandleMsg);

    Helper::Window::Register(WND_CLASS_NAME, registerInfo);
}

void ApplicationWinImp::ShowWin32Window(int width, int height, const std::string& windowName)
{
    Helper::Window::StyleInfo style {};
    style.canResize = true;
    style.hasSysmenu = true;
    style.hasMaxBtn = false;
    style.hasMinBtn = false;

    // send self via WM_NCCREATE. build the relationship between instance pointer and win api.
    void* lParam = this;

    _pWindow = Helper::Window::Show(WND_CLASS_NAME, windowName, width, height, style, lParam);
}

void ApplicationWinImp::DestroyWindow()
{
    Helper::Window::Destroy(std::move(_pWindow));
}

void ApplicationWinImp::UnRegisterWindow()
{
    Helper::Window::UnRegister(WND_CLASS_NAME);
}


