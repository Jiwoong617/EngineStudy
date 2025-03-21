#include "jwSpriteRenderer.h"
#include "jwGameObject.h"
#include "jwTransform.h"

namespace jw
{
    SpriteRenderer::SpriteRenderer()
        : mImgae(nullptr)
        , mWidth(0)
        , mHeight(0)
    {
    }
    SpriteRenderer::~SpriteRenderer()
    {
    }
    void SpriteRenderer::Initialize()
    {
    }
    void SpriteRenderer::Update()
    {
    }
    void SpriteRenderer::LateUpdate()
    {
    }

    void SpriteRenderer::Render(HDC hdc)
    {
        Transform* tr = GetOwner()->GetComponent<Transform>();
        math::Vector2 pos = tr->GetPosition();

        Gdiplus::Graphics graphcis(hdc);
        graphcis.DrawImage(mImgae, Gdiplus::Rect(pos.x, pos.y, mWidth, mHeight));
    }

    void SpriteRenderer::ImageLoad(const std::wstring& path)
    {
        mImgae = Gdiplus::Image::FromFile(path.c_str());
        mWidth = mImgae->GetWidth();
        mHeight = mImgae->GetHeight();
    }
}