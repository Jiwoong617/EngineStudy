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
#include "jwAnimator.h"


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


        mPlayer = object::Instantiate<Player>(enums::eLayerType::Particle);
        mPlayer->AddComponent<PlayerScript>();

        graphics::Texture* packmanTexture = Resources::Find<graphics::Texture>(L"Cat");
        Animator* animator = mPlayer->AddComponent<Animator>();
        animator->CreateAnimation(L"DownWalk", packmanTexture
            , Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        animator->CreateAnimation(L"RightWalk", packmanTexture
            , Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        animator->CreateAnimation(L"UpWalk", packmanTexture
            , Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        animator->CreateAnimation(L"LeftWalk", packmanTexture
            , Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        animator->CreateAnimation(L"SitDown", packmanTexture
            , Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        animator->CreateAnimation(L"Grooming", packmanTexture
            , Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);

        animator->PlayAnimation(L"SitDown", false);

        mPlayer->GetComponent<Transform>()->SetPosition(Vector2(100.0f, 100.0f));
        mPlayer->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));

        GameObject* bg = object::Instantiate<GameObject>(enums::eLayerType::Player);
        SpriteRenderer* bgSr = bg->AddComponent<SpriteRenderer>();

        graphics::Texture* bgTexture = Resources::Find<graphics::Texture>(L"Bubble");
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