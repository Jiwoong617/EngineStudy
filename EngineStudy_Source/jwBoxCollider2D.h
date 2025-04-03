#pragma once
#include "jwCollider.h"

namespace jw
{
    class BoxCollider2D : public Collider
    {
    public:
        BoxCollider2D();
        ~BoxCollider2D();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render(HDC hdc);

    private:
        //박스는 사이즈
        //Vector2 mSize;
    };
}