#pragma once

#include "Application/AppLooper.h"
#include "Application/ApplicationWinImp/IWinMsgReceiver.h"
#include "Editor/Editor.h"

class EditorLooper : public AppLooper, public IWinMsgReceiver
{
public:
    EditorLooper();
    ~EditorLooper() override;

public:
    void Loop() override;
    void OnWinMsg(int64_t hWnd, uint32_t msg, int64_t wParam, int64_t lParam) override;

private:
    Editor::Editor* _pEditor = nullptr;
};