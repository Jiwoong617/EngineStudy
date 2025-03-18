#include "jwPlayScene.h"
#include "jwGameObject.h"
#include "jwTransform.h"
#include "jwSpriteRenderer.h"
#include "jwPlayer.h"

namespace jw
{
    PlayScene::PlayScene()
    {
    }
    PlayScene::~PlayScene()
    {
    }
    void PlayScene::Initialize()
    {
        Player* pl = new Player();
        Transform* tr = pl->AddComponent<Transform>();
        tr->SetPos(800, 450);

        tr->SetName(L"TR");

        SpriteRenderer* sr = pl->AddComponent<SpriteRenderer>();
        sr->SetName(L"SR");

        AddGameObject(pl);
    }

    void PlayScene::Update()
    {
        Scene::Update();
    }
    void PlayScene::LateUpdate()
    {
        Scene::LateUpdate();
    }
    void PlayScene::Render(HDC hdc)
    {
        Scene::Render(hdc);
    }
}