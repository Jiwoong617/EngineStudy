#pragma once
#include "..\\EngineStudy_Source\\jwScene.h"

namespace jw
{
    class TitleScene : public Scene
    {
    public:
        TitleScene();
        ~TitleScene();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC hdc) override;


        void OnEnter() override;
        void OnExit()  override;
    private:
    };
}