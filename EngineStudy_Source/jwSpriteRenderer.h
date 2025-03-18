#pragma once
#include "jwEntity.h"
#include "jwComponent.h"

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

        void ImageLoad(const std::wstring& path);

    private:
        Gdiplus::Image* mImgae;
        UINT mWidth;
        UINT mHeight;
    };
}