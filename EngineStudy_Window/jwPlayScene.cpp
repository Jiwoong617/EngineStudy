#include "jwPlayScene.h"
#include "jwGameObject.h"
#include "jwTransform.h"
#include "jwSpriteRenderer.h"
#include "jwPlayer.h"
#include "jwInput.h"
#include "jwTitleScene.h"
#include "jwSceneManager.h"
#include "jwObject.h"
#include "jwTexture.h"
#include "jwResources.h"
#include "jwPlayerScript.h"
#include "jwCamera.h"
#include "jwRenderer.h"


namespace jw
{
    PlayScene::PlayScene()
        : mPlayer(nullptr)
    {
    }
    PlayScene::~PlayScene()
    {
    }

    void PlayScene::Initialize()
    {
        // main camera
        GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(344.0f, 442.0f));
        Camera* cameraComp = camera->AddComponent<Camera>();
        renderer::mainCamera = cameraComp;


        //플레이어
        mPlayer = object::Instantiate<Player>
            (enums::eLayerType::Player/*, Vector2(100.0f, 100.0f)*/);
        SpriteRenderer* sr = mPlayer->AddComponent<SpriteRenderer>();
        sr->SetSize(Vector2(3.0f, 3.0f));
        mPlayer->AddComponent<PlayerScript>();
        //플레이어에 팩맨 텍스쳐 set
        graphics::Texture* packmanTexture = Resources::Find<graphics::Texture>(L"PackMan");
        sr->SetTexture(packmanTexture);


        //배경
        GameObject* bg = object::Instantiate<GameObject>
            (enums::eLayerType::BackGround/*, Vector2(100.0f, 100.0f)*/);
        SpriteRenderer* bgSr = bg->AddComponent<SpriteRenderer>();
        bgSr->SetSize(Vector2(3.0f, 3.0f));

        graphics::Texture* bgTexture = Resources::Find<graphics::Texture>(L"Map");
        bgSr->SetTexture(bgTexture);

        // 게임 오브젝트 생성후 레이어와 게임오브젝트들의 init함수를 호출
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