#pragma once

#include "jwEntity.h"
#include "jwComponent.h"

namespace jw
{
    using namespace math;

    class Transform : public Component
    {
    public:
        Transform();
        ~Transform();

        void Initialize() override;
        void Update()  override;
        void LateUpdate()  override;
        void Render(HDC hdc)  override;

        Vector2 GetPosition() { return mPosition; }
        void SetPosition(Vector2 pos) { mPosition.x = pos.x; mPosition.y = pos.y; }
        
        float GetRoation() { return mRotation; }
        void SetRotation(float rotate) { mRotation = rotate; }
        
        Vector2 GetScale() { return mScale; }
        void SetScale(Vector2 scale) { mScale = scale; }

    private:
        Vector2 mPosition;
        Vector2 mScale;
        float mRotation;
    };
}