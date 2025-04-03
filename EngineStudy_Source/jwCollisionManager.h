#pragma once
#include "CommonInclude.h"
#include "jwBoxCollider2D.h"
#include "jwCircleCollider2D.h"


namespace jw
{
    using namespace enums;
    class CollisionManager
    {
    public:
        static void Initialize();
        static void Update();
        static void LateUpdate();
        static void Render(HDC hdc);

        static void CollisionLayerCheck(eLayerType left, eLayerType right, bool enable);
        static void LayerCollision(class Scene* scene, eLayerType left, eLayerType right);
        static void ColliderCollision(Collider* left, Collider* right);

    private:
        //유니티 레이어 표 같은 것
        //체크만 하면 되니 1bit만 사용 - bit 연산 사용
        static std::bitset<(UINT)eLayerType::Max> mCollisionLayerMatrix[(UINT)eLayerType::Max];
    };
}