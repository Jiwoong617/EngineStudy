#include "jwAnimation.h"
#include "jwTime.h"
#include "jwTransform.h"
#include "jwGameObject.h"
#include "jwAnimator.h"
#include "jwRenderer.h"
#include "jwCamera.h"

namespace jw
{
    Animation::Animation()
        : Resource(enums::eResourceType::Animation)
        , mAnimator(nullptr)
        , mTexture(nullptr)
        , mAnimationSheet{}
        , mIndex(-1)
        , mTime(0.0f)
        , mbComplete(false)
    {
    }

    Animation::~Animation()
    {
    }

    HRESULT Animation::Load(const std::wstring& path)
    {
        return E_NOTIMPL;
    }

    void Animation::Update()
    {
        if (mbComplete)
            return;

        mTime += Time::DeltaTime();

        if (mAnimationSheet[mIndex].duration < mTime)
        {
            mTime = 0.0f; //타임 초기화
            if (mIndex < mAnimationSheet.size() - 1)
                mIndex++;
            else
                mbComplete = true;
        }
    }

    void Animation::Render(HDC hdc)
    {
        // 알파블렌드 사용 조건 : 해당이미지 알파채널이 있어야함
        if (mTexture == nullptr)
            return;

        GameObject* gameObj = mAnimator->GetOwner();
        Transform* tr = gameObj->GetComponent<Transform>();
        Vector2 pos = tr->GetPosition();
        Vector2 scale = tr->GetScale();
        float rot = tr->GetRoation();

        if (renderer::mainCamera)
            pos = renderer::mainCamera->CaluatePosition(pos);

        Sprite sprite = mAnimationSheet[mIndex];
        graphics::Texture::eTextureType type = mTexture->GetTextureType();

        if (type == graphics::Texture::eTextureType::Bmp)
        {
            //알파 블렌드 투명 설정
            /*BLENDFUNCTION func = {};
            func.BlendOp = AC_SRC_OVER;
            func.BlendFlags = 0;
            func.AlphaFormat = AC_SRC_ALPHA;
            func.SourceConstantAlpha = 255;*/ // 0(투명) ~ 255(Opaque-불투명)

            HDC imgHdc = mTexture->GetHdc();

            /*AlphaBlend(hdc
                , pos.x - (sprite.size.x / 2.0f)
                , pos.y - (sprite.size.y / 2.0f)
                , sprite.size.x * scale.x
                , sprite.size.y * scale.y
                , imgHdc
                , sprite.leftTop.x
                , sprite.leftTop.y
                , sprite.size.x
                , sprite.size.y
                , func);*/
            TransparentBlt(hdc
                , pos.x - (sprite.size.x / 2.0f)
                , pos.y - (sprite.size.y / 2.0f)
                , sprite.size.x * scale.x
                , sprite.size.y * scale.y
                , imgHdc
                , sprite.leftTop.x
                , sprite.leftTop.y
                , sprite.size.x
                , sprite.size.y
                , RGB(255, 0, 255));
        }
        else if (type == graphics::Texture::eTextureType::Png)
        {
            //원하는 픽셀 투명화하고 싶을 때
            Gdiplus::ImageAttributes imgAtt = {};
            //픽셀 색 범위
            imgAtt.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));

            Gdiplus::Graphics graphics(hdc);

            graphics.TranslateTransform(pos.x, pos.y);
            graphics.RotateTransform(rot);
            graphics.TranslateTransform(-pos.x, -pos.y);

            graphics.DrawImage(mTexture->GetImage()
                , Gdiplus::Rect
                (   // 이미지 피벗 중앙으로 만들기
                    pos.x - (sprite.size.x / 2.0f)
                    , pos.y - (sprite.size.y / 2.0f)
                    , sprite.size.x * scale.x
                    , sprite.size.y * scale.y
                )
                , sprite.leftTop.x
                , sprite.leftTop.y
                , sprite.size.x
                , sprite.size.y
                , Gdiplus::UnitPixel
                , nullptr
            );
        }

    }

    void Animation::CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet
        , Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLegth, float duration)
    {
        mTexture = spriteSheet;
        for (size_t i = 0; i < spriteLegth; i++)
        {
            Sprite sprite = {};
            sprite.leftTop.x = leftTop.x + (size.x * i);
            sprite.leftTop.y = leftTop.y;
            sprite.size = size;
            sprite.offset = offset;
            sprite.duration = duration;

            mAnimationSheet.push_back(sprite);
        }
    }

    void Animation::Reset()
    {
        mTime = 0.0f;
        mIndex = 0;
        mbComplete = false;
    }
}