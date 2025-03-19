#pragma once
#include "jwEntity.h"
#include "CommonInclude.h"
#include "jwGameObject.h"

namespace jw
{
    class Layer : public Entity
    {
    public:
        Layer();
        ~Layer();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render(HDC hdc);

        void AddGameObject(GameObject* gameObject);

    private:
        std::vector<GameObject*> mGameObjects;
    };
}