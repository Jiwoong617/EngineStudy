#include "jwPlayerScript.h"
#include "jwInput.h"
#include "jwTransform.h"
#include "jwTime.h"
#include "jwGameObject.h"
#include "jwAnimator.h"
#include "jwCat.h"
#include "jwCatScript.h"
#include "jwObject.h"
#include "jwResources.h"


namespace jw
{
    PlayerScript::PlayerScript()
        : mState(PlayerScript::eState::Idle)
        , mAnimator(nullptr)
    {
    }
    PlayerScript::~PlayerScript()
    {
    }

    void PlayerScript::Initialize()
    {
    }

    void PlayerScript::Update()
    {
		if (mAnimator == nullptr)
		{
			mAnimator = GetOwner()->GetComponent<Animator>();
		}

		switch (mState)
		{
		case PlayerScript::eState::Idle:
			idle();
			break;

		case PlayerScript::eState::Walk:
			move();
			break;

		case PlayerScript::eState::Sleep:
			break;

		case PlayerScript::eState::GiveWater:
			giveWater();
			break;

		case PlayerScript::eState::Attack:
			break;

		default:
			break;
		}
    }

    void PlayerScript::LateUpdate()
    {
    }

    void PlayerScript::Render(HDC hdc)
    {
    }

	void PlayerScript::AttackEffect()
	{
		Cat* cat = object::Instantiate<Cat>(enums::eLayerType::Animal);
		CatScript* catSrc = cat->AddComponent<CatScript>();

		catSrc->SetPlayer(GetOwner());

		graphics::Texture* catTex = Resources::Find<graphics::Texture>(L"Cat");
		Animator* catAnimator = cat->AddComponent<Animator>();
		catAnimator->CreateAnimation(L"DownWalk", catTex
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

		catAnimator->PlayAnimation(L"SitDown", false);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		cat->GetComponent<Transform>()->SetPosition(tr->GetPosition());
		cat->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));


		Vector2 mousePos = Input::GetMousePosition();
		catSrc->mDest = mousePos;
	}

	void PlayerScript::idle()
	{
		if (Input::GetKey(eKeyCode::LButton))
		{
			//mState = PlayerScript::eState::GiveWater;
			//mAnimator->PlayAnimation(L"FrontGiveWater", false);
			Cat* cat = object::Instantiate<Cat>(enums::eLayerType::Animal);
			CatScript* catSrc = cat->AddComponent<CatScript>();

			catSrc->SetPlayer(GetOwner());

			graphics::Texture* catTex = Resources::Find<graphics::Texture>(L"Cat");
			Animator* catAnimator = cat->AddComponent<Animator>();
			catAnimator->CreateAnimation(L"DownWalk", catTex
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

			catAnimator->PlayAnimation(L"SitDown", false);

			Transform* tr = GetOwner()->GetComponent<Transform>();

			cat->GetComponent<Transform>()->SetPosition(tr->GetPosition() /*+ Vector2(100.0f, 0.0f)*/);
			cat->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));



			Vector2 mousePos = Input::GetMousePosition();
			catSrc->mDest = mousePos;
		}

		if (Input::GetKey(eKeyCode::A))
			mState = PlayerScript::eState::Walk;
		if (Input::GetKey(eKeyCode::W))
			mState = PlayerScript::eState::Walk;
		if (Input::GetKey(eKeyCode::S))
			mState = PlayerScript::eState::Walk;
		if (Input::GetKey(eKeyCode::D))
			mState = PlayerScript::eState::Walk;
	}

	void PlayerScript::move()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::D))
			pos.x += 100.0f * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::A))
			pos.x -= 100.0f * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::W))
			pos.y -= 100.0f * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::S))
			pos.y += 100.0f * Time::DeltaTime();

		tr->SetPosition(pos);

		if (Input::GetKeyUp(eKeyCode::D) || Input::GetKeyUp(eKeyCode::A)
			|| Input::GetKeyUp(eKeyCode::W) || Input::GetKeyUp(eKeyCode::S))
		{
			mState = PlayerScript::eState::Idle;
			mAnimator->PlayAnimation(L"Idle", false);
		}
	}

	void PlayerScript::giveWater()
	{
		if (mAnimator->IsComplete())
		{
			mState = eState::Idle;
			mAnimator->PlayAnimation(L"Idle", false);
		}
	}
}