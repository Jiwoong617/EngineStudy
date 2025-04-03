#pragma once
#include "jwEntity.h"
#include "CommonInclude.h"
#include "jwGameObject.h"

namespace jw
{
    typedef std::vector<GameObject*>::iterator GameObjectIter;

    class Layer : public Entity
    {
    public:
        Layer();
        ~Layer();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render(HDC hdc);
        virtual void Destroy();

        void AddGameObject(GameObject* gameObject);
        //���� ����Ǹ� �ȵ� - const
        const std::vector<GameObject*> GetGameObjects() { return mGameObjects; }

    private:
        void findDeadGameObjects(OUT std::vector<GameObject*>& gameObjs);
        void deleteGameObjects(std::vector<GameObject*> gameObjs);
        void eraseGameObject();

    private:
        std::vector<GameObject*> mGameObjects;
    };
}