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

        void SetPlayer(GameObject* player) { mPlayer = player; }

    private:
        void sitDown();
        void move();
        void layDown();

        void playWalkAnimationByDirection(eDirection dir);
        void translate(Transform* tr);

    public:
        Vector2 mDest;

    private:
        eState mState;
        class Animator* mAnimator;
        eDirection mDirection;
        float mTime;
        float mDeathTime;

        GameObject* mPlayer;
        float mRadian;
    };
}