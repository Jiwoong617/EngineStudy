#include "jwCollisionManager.h"
#include "jwSceneManager.h"
#include "jwGameObject.h"
#include "jwCollider.h"
#include "jwTransform.h"

namespace jw
{
    std::bitset<(UINT)eLayerType::Max> CollisionManager::mCollisionLayerMatrix[(UINT)eLayerType::Max] = {};
    std::unordered_map<UINT64, bool> CollisionManager::mCollisionMap = {};

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
        // 두 충돌체 번호로 가져온 ID 확인하여 CollisionID 세팅
        CollisionID id = {};
        id.left = left->GetID();
        id.right = right->GetID();

        // 이전 충돌 정보를 검색
        // 충돌정보가 없으면 - 충돌정보를 생성
        auto iter = mCollisionMap.find(id.id);
        if (iter == mCollisionMap.end())
        {
            mCollisionMap.insert(std::make_pair(id.id, false));
            iter = mCollisionMap.find(id.id);
        }

        // 충돌 체크
        if (Intersect(left, right))
        {
            //처음 충돌
            if (iter->second == false)
            {
                left->OnCollisionEnter(right);
                right->OnCollisionEnter(left);
                iter->second = true;
            }
            else //충돌 중
            {
                left->OnCollisionStay(right);
                right->OnCollisionStay(left);
            }
        }
        else //충돌 중이 아닐 때
        {
            //이전 프레임에 충돌이 있었으면 - 충돌이 끝남
            if (iter->second == true)
            {
                left->OnCollisionExit(right);
                right->OnCollisionExit(left);

                iter->second = false;
            }
        }
    }


    bool CollisionManager::Intersect(Collider* left, Collider* right)
    {
        Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
        Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

        Vector2 leftPos = leftTr->GetPosition() + left->GetOffset();
        Vector2 rightPos = rightTr->GetPosition() + right->GetOffset();

        //size (1,1) 일 때 기본 크기가 100픽셀
        Vector2 leftSize = left->GetSize() * 100.0f;
        Vector2 rightSize = right->GetSize() * 100.0f;

        //AABB 충돌
        if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
            && fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.0f + rightSize.y / 2.0f))
        {
            return true;
        }

        return false;
    }
}