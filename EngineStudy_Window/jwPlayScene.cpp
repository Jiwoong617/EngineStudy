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
#include "jwCat.h"
#include "jwCatScript.h"
#include "jwBoxCollider2D.h"
#include "jwCollisionManager.h"


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
        CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Animal, true);

        // main camera
        GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(344.0f, 442.0f));
        Camera* cameraComp = camera->AddComponent<Camera>();
        renderer::mainCamera = cameraComp;

        //player
        mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);
        PlayerScript* plScript = mPlayer->AddComponent<PlayerScript>();

        //콜라이더
        //BoxCollider2D* collider = mPlayer->AddComponent<BoxCollider2D>();
        CircleCollider2D* collider = mPlayer->AddComponent<CircleCollider2D>();
        collider->SetOffset(Vector2(-50.0f, -50.0));

        graphics::Texture* playerTex = Resources::Find<graphics::Texture>(L"Player");
        Animator* playerAnimator = mPlayer->AddComponent<Animator>();
        playerAnimator->CreateAnimation(L"Idle", playerTex
            , Vector2(2000.0f, 250.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 1, 0.1f);
        playerAnimator->CreateAnimation(L"FrontGiveWater", playerTex
            , Vector2(0.0f, 2000.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 12, 0.1f);
        playerAnimator->PlayAnimation(L"Idle", false);

        //FrontGiveWater 애니메이션의 CompleteEvent에 PlayerScript에 있는 AttackEffect를 bind를 사용해 넣어주기
        playerAnimator->GetCompleteEvent(L"FrontGiveWater") = std::bind(&PlayerScript::AttackEffect, plScript);

        mPlayer->GetComponent<Transform>()->SetPosition(Vector2(100.0f, 100.0f));

        //cat
        Cat* cat = object::Instantiate<Cat>(enums::eLayerType::Animal);
        cat->AddComponent<CatScript>();

        graphics::Texture* catTex = Resources::Find<graphics::Texture>(L"Cat");
        Animator* catAnimator = cat->AddComponent<Animator>();

        CircleCollider2D* boxCatCollider = cat->AddComponent<CircleCollider2D>();
        boxCatCollider->SetOffset(Vector2(-50.0f, -50.0f));

        /*catAnimator->CreateAnimation(L"DownWalk", catTex
            , Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        catAnimator->CreateAnimation(L"RightWalk", catTex
            , Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        catAnimator->CreateAnimation(L"UpWalk", catTex
            , Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        catAnimator->CreateAnimation(L"LeftWalk", catTex
            , Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        catAnimator->CreateAnimation(L"SitDown", catTex
            , Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        catAnimator->CreateAnimation(L"Grooming", catTex
            , Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        catAnimator->CreateAnimation(L"LayDown", catTex
            , Vector2(0.0f, 192.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);

        catAnimator->PlayAnimation(L"SitDown", false);*/
        catAnimator->CreateAnimationByFolder(L"MushroomIdle", L"..\\Resources\\Mushroom", Vector2::Zero, 0.1f);

        catAnimator->PlayAnimation(L"MushroomIdle", true);

        cat->GetComponent<Transform>()->SetPosition(Vector2(200.0f, 200.0f));
        cat->GetComponent<Transform>()->SetScale(Vector2(1.0f, 1.0f));
        
        //cameraComp->SetTarget(cat);

        //bg
        //GameObject* bg = object::Instantiate<GameObject>(enums::eLayerType::Player);
        //SpriteRenderer* bgSr = bg->AddComponent<SpriteRenderer>();

        //graphics::Texture* bgTexture = Resources::Find<graphics::Texture>(L"Bubble");
        //bgSr->SetTexture(bgTexture);

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
        Scene::OnEnter();
    }

    void PlayScene::OnExit()
    {
        Scene::OnExit();
    }
}