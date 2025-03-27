#pragma once
#include "..\\EngineStudy_Source\\jwScript.h"
#include "..\\EngineStudy_Source\\jwTransform.h"

namespace jw
{
    class CatScript : public Script
    {
    public:
        enum class eState
        {
            SitDown,
            Walk,
            Sleep,
            LayDown,
            Attack,
        };

        enum class eDirection
        {
            Left,
            Right,
            Down,
            Up,
            End,
        };

        CatScript();
        ~CatScript();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC hdc) override;

    private:
        void sitDown();
        void move();
        void layDown();

        void playWalkAnimationByDirection(eDirection dir);
        void translate(Transform* tr);

    private:
        eState mState;
        class Animator* mAnimator;
        eDirection mDirection;
        float mTime;

    };
}