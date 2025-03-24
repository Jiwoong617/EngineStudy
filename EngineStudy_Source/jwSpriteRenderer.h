#pragma once
#include "jwEntity.h"
#include "jwComponent.h"
#include "jwTexture.h"

namespace jw
{
    class SpriteRenderer : public Component
    {
    public:
        SpriteRenderer();
        ~SpriteRenderer();

        void Initialize() override;
        void Update()  override;
        void LateUpdate()  override;
        void Render(HDC hdc)  override;

        void SetTexture(graphics::Texture* texture) { mTexture = texture; }
        void SetSize(math::Vector2 size) { mSize = size; }


    private:
        graphics::Texture* mTexture;
        math::Vector2 mSize;
    };
}