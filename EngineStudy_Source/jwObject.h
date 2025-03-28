#pragma once
#include "jwComponent.h"
#include "jwGameObject.h"
#include "jwLayer.h"
#include "jwScene.h"
#include "jwSceneManager.h"
#include "jwTransform.h"


namespace jw::object
{
    template <typename T>
    static T* Instantiate(jw::enums::eLayerType type)
    {
        T* gameObject = new T();
        Scene* activeScene = SceneManager::GetActiveScene();
        Layer* layer = activeScene->GetLayer(type);
        layer->AddGameObject(gameObject);

        return gameObject;
    }

    template <typename T>
    static T* Instantiate(jw::enums::eLayerType type, math::Vector2 position)
    {
        T* gameObject = new T();
        Scene* activeScene = SceneManager::GetActiveScene();
        Layer* layer = activeScene->GetLayer(type);
        layer->AddGameObject(gameObject);

        Transform* tr = gameObject->GetComponent<Transform>();
        tr->SetPosition(position);

        return gameObject;
    }

    static void Destroy(GameObject* obj)
    {
        obj->Death();
    }
}