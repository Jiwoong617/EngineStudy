#include "jwTilemapRenderer.h"
#include "jwGameObject.h"
#include "jwTransform.h"
#include "jwTexture.h"
#include "jwRenderer.h"

namespace jw
{
    TilemapRenderer::TilemapRenderer()
        : Component(enums::eComponentType::SpriteRenderer)
        , mTexture(nullptr)
        , mSize(3.0f, 3.0f)
        , mIndex(8, 7)
        , mTileSize(16.0f, 16.0f)
    {
    }
    TilemapRenderer::~TilemapRenderer()
    {
    }
    void TilemapRenderer::Initialize()
    {


    }
    void TilemapRenderer::Update()
    {

    }

    void TilemapRenderer::LateUpdate()
    {
    }

    void TilemapRenderer::Render(HDC hdc)
    {
        if (mTexture == nullptr) assert(false);

        Transform* tr = GetOwner()->GetComponent<Transform>();
        Vector2 pos = tr->GetPosition();
        Vector2 scale = tr->GetScale();
        float rot = tr->GetRoation();

        pos = renderer::mainCamera->CaluatePosition(pos);
        if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Bmp)
        {
            if (mTexture->IsAlpha())
            {
                BLENDFUNCTION func = {};
                func.BlendOp = AC_SRC_OVER;
                func.BlendFlags = 0;
                func.AlphaFormat = AC_SRC_ALPHA;
                func.SourceConstantAlpha = 255;

                AlphaBlend(hdc
                    , pos.x, pos.y
                    , mTileSize.x * mSize.x * scale.x
                    , mTileSize.y * mSize.y * scale.y
                    , mTexture->GetHdc()
                    , mIndex.x * mTileSize.x, mIndex.y * mTileSize.y
                    , mTileSize.x
                    , mTileSize.y
                    , func);
            }
            else
            {
                TransparentBlt(hdc
                    , pos.x, pos.y
                    , mTileSize.x * mSize.x * scale.x
                    , mTileSize.y * mSize.y * scale.y
                    , mTexture->GetHdc()
                    , mIndex.x * mTileSize.x, mIndex.y * mTileSize.y
                    , mTileSize.x
                    , mTileSize.y
                    , RGB(255, 0, 255));
            }
        }
    }

}