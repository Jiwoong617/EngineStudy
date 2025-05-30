#pragma once
#include "jwCollider.h"

namespace jw
{
    class CircleCollider2D : public Collider
    {
    public:
        CircleCollider2D();
        ~CircleCollider2D();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render(HDC hdc);

    private:
        //원은 반지름
        float mRadius;
    };
}