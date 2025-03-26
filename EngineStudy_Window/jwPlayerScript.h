#pragma once
#include "..\\EngineStudy_Source\\jwScript.h"


namespace jw
{
    class PlayerScript : public Script
    {
    public:
        enum class eState
        {
            SitDown,
            Walk,
            Sleep,
            Attack,
        };

        PlayerScript();
        ~PlayerScript();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC hdc) override;

    private:
        void sitdown();
        void move();

    private:
        eState mState;
        class Animator* mAnimator;
    };
}