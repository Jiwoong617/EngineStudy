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
        // gameobject ���漱��
        class GameObject* mTarget;
        Vector2 mDistance; //ī�޶� ��ġ(�Ÿ�)
        Vector2 mResolution; //ȭ�� �ػ�
        Vector2 mLookPosition; //ī�޶� ����(�ٶ󺸴� ��ġ)
    };
}