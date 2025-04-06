#pragma once
#include "..\\EngineStudy_Source\\jwScene.h"

namespace jw
{
    class ToolScene : public Scene
    {
    public:
        ToolScene();
        ~ToolScene();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC hdc) override;

        void OnEnter() override;
        void OnExit()  override;


    };
}

LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);