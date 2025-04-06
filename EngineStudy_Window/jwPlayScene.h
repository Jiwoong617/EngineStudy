#pragma once
#include "..\\EngineStudy_Source\\jwScene.h"

namespace jw
{
    class PlayScene : public Scene
    {
    public:
        PlayScene();
        ~PlayScene();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC hdc) override;


        void OnEnter() override;
        void OnExit()  override;

    private:
		void loadTilemap();

    private:
        class Player* mPlayer;
    };
}