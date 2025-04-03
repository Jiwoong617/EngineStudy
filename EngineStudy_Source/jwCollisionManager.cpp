#include "jwCollisionManager.h"
#include "jwSceneManager.h"
#include "jwGameObject.h"
#include "jwCollider.h"

namespace jw
{

    std::bitset<(UINT)eLayerType::Max> CollisionManager::mCollisionLayerMatrix[(UINT)eLayerType::Max] = {};

    void CollisionManager::Initialize()
    {
    }

    void CollisionManager::Update()
    {
        Scene* scene = SceneManager::GetActiveScene();
        for (UINT row = 0; row < (UINT)eLayerType::Max; row++)
        {
            for (UINT col = 0; col < (UINT)eLayerType::Max; col++)
            {
                if (mCollisionLayerMatrix[row][col] == true)
                {
                    LayerCollision(scene, (eLayerType)row, (eLayerType)col);
                }
            }
        }
    }

    void CollisionManager::LateUpdate()
    {
    }

    void CollisionManager::Render(HDC hdc)
    {
    }

    //어떤 레이어들 간에 충돌을 할 건지
    void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
    {
        int row = 0;
        int col = 0;

        if (left <= right)
        {
            row = (UINT)left;
            col = (UINT)right;
        }
        else
        {
            row = (UINT)right;
            col = (UINT)left;
        }

        mCollisionLayerMatrix[row][col] = enable;
    }

    void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
    {
        //scene 의 레이어 내부의 게임옵젝 가져오기
        const std::vector<GameObject*>& lefts = scene->GetLayer(left)->GetGameObjects();
        const std::vector<GameObject*>& rights = scene->GetLayer(right)->GetGameObjects();

        //두 게임옵젝 충돌 처리
        for (GameObject* left : lefts)
        {
            //비활성화 or 콜라이더 없으면 넘기기
            if (left->IsActive() == false)
                continue;
            Collider* leftCol = left->GetComponent<Collider>();
            if (leftCol == nullptr)
                continue;

            for (GameObject* right : rights)
            {
                if (right->IsActive() == false)
                    continue;
                Collider* rightCol = right->GetComponent<Collider>();
                if (rightCol == nullptr)
                    continue;

                //같은 레이어의 같은 옵젝 ex)동일한 옵젝이면 넘기기
                if (left == right)
                    continue;

                ColliderCollision(leftCol, rightCol);
            }
        }
    }

    void CollisionManager::ColliderCollision(Collider* left, Collider* right)
    {
        //충돌체크로직 작성
    }

}