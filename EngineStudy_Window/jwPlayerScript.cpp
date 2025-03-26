#include "jwPlayerScript.h"
#include "jwInput.h"
#include "jwTransform.h"
#include "jwTime.h"
#include "jwGameObject.h"
#include "jwAnimator.h"

namespace jw
{
    PlayerScript::PlayerScript()
        : mState(PlayerScript::eState::SitDown)
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
		case PlayerScript::eState::SitDown:
			sitdown();
			break;

		case PlayerScript::eState::Walk:
			move();
			break;

		case PlayerScript::eState::Sleep:
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

	void PlayerScript::sitdown()
	{
		if (Input::GetKey(eKeyCode::D))
		{
			mState = PlayerScript::eState::Walk;
			mAnimator->PlayAnimation(L"RightWalk");
		}
		if (Input::GetKey(eKeyCode::A))
			mState = PlayerScript::eState::Walk;
		if (Input::GetKey(eKeyCode::W))
			mState = PlayerScript::eState::Walk;
		if (Input::GetKey(eKeyCode::S))
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
			mState = PlayerScript::eState::SitDown;
			mAnimator->PlayAnimation(L"SitDown", false);
		}
	}
}