#include "jwPlayScene.h"
#include "jwGameObject.h"
#include "jwTransform.h"
#include "jwSpriteRenderer.h"
#include "jwPlayer.h"
#include "jwInput.h"
#include "jwTitleScene.h"
#include "jwSceneManager.h"
#include "jwObject.h"

namespace jw
{
    PlayScene::PlayScene():bg(nullptr)
    {
    }
    PlayScene::~PlayScene()
    {
    }
    void PlayScene::Initialize()
    {
        bg = object::Instantiate<Player>(enums::eLayerType::BackGround, Vector2(100.f, 100.f));

        SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
        sr->ImageLoad(L"..\\Resources\\BgImage.jpg");

        Scene::Initialize();
    }

    void PlayScene::Update()
    {
        Scene::Update();
    }

    void PlayScene::LateUpdate()
    {
        Scene::LateUpdate();
        if (Input::GetKeyDown(eKeyCode::N))
        {
            SceneManager::LoadScene(L"TitleScene");
        }
    }

    void PlayScene::Render(HDC hdc)
    {
        Scene::Render(hdc);

        wchar_t str[50] = L"Play Scene";
        TextOut(hdc, 0, 0, str, 10);
    }

    void PlayScene::OnEnter()
    {
    }

    void PlayScene::OnExit()
    {

    }
}