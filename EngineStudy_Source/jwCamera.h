#pragma once
#include "jwComponent.h"


namespace jw
{
    using namespace jw::math;
    class Camera : public Component
    {
    public:
        Vector2 CaluatePosition(Vector2 pos) { return pos - mDistance; };

        Camera();
        ~Camera();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC hdc) override;

    private:
        // gameobject 전방선언
        class GameObject* mTarget;
        Vector2 mDistance; //카메라 위치(거리)
        Vector2 mResolution; //화면 해상도
        Vector2 mLookPosition; //카메라 원점(바라보는 위치)
    };
}