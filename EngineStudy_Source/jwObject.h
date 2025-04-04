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
        gameObject->SetLayerType(type);
        Scene* activeScene = SceneManager::GetActiveScene();
        Layer* layer = activeScene->GetLayer(type);
        layer->AddGameObject(gameObject);

        return gameObject;
    }

    template <typename T>
    static T* Instantiate(jw::enums::eLayerType type, math::Vector2 position)
    {
        T* gameObject = new T();
        gameObject->SetLayerType(type);
        Scene* activeScene = SceneManager::GetActiveScene();
        Layer* layer = activeScene->GetLayer(type);
        layer->AddGameObject(gameObject);

        Transform* tr = gameObject->GetComponent<Transform>();
        tr->SetPosition(position);

        return gameObject;
    }

    static void DontDestroyOnLoad(GameObject* gameObject)
    {
        Scene* activeScene = SceneManager::GetActiveScene();
        // 현재씬에서 게임오브젝트 삭제
        activeScene->EraseGameObject(gameObject);

        // 해당 게임오브젝트를 -> DontDestroy씬으로 넣기
        Scene* dontDestroyOnLoad = SceneManager::GetDontDestroyOnLoad();
        dontDestroyOnLoad->AddGameObject(gameObject, gameObject->GetLayerType());
    }
}