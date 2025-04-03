#include "jwCatScript.h"
#include "jwInput.h"
#include "jwTransform.h"
#include "jwTime.h"
#include "jwGameObject.h"
#include "jwAnimator.h"
#include "jwObject.h"

namespace jw
{
    CatScript::CatScript()
        : mState(CatScript::eState::SitDown)
        , mAnimator(nullptr)
        , mTime(0.0f)
        , mDeathTime(0.0f)
        , mDest(Vector2::Zero)
        , mRadian(0.0f)
    {
    }
    CatScript::~CatScript()
    {
    }

    void CatScript::Initialize()
    {


    }

    void CatScript::Update()
    {
        mDeathTime += Time::DeltaTime();
        if (mDeathTime > 6.0f)
        {
            //object::Destroy(GetOwner());
        }

        if (mAnimator == nullptr)
        {
            mAnimator = GetOwner()->GetComponent<Animator>();
        }

        switch (mState)
        {
        case CatScript::eState::SitDown:
            sitDown();
            break;
        case CatScript::eState::Walk:
            move();
            break;

        case CatScript::eState::Sleep:
            break;
        case CatScript::eState::LayDown:

            break;
        case CatScript::eState::Attack:
            break;
        default:
            break;
        }

    }

    void CatScript::LateUpdate()
    {
    }

    void CatScript::Render(HDC hdc)
    {
    }

    void CatScript::sitDown()
    {
        mTime += Time::DeltaTime();

        Transform* tr = GetOwner()->GetComponent<Transform>();
        Vector2 pos = tr->GetPosition();

        // 삼각함수를 통한 이동
        //mRadian += 5.0f * Time::DeltaTime();
        //pos += Vector2(1.0f, 2.0f * cosf(mRadian)) * (100.0f * Time::DeltaTime());

        //Transform* plTr = mPlayer->GetComponent<Transform>();
        //Vector2 dest = mDest - plTr->GetPosition();
        //dest.normalize();

        //float rotDegree = Vector2::Dot(dest, Vector2::Right); //cos세타
        //rotDegree = acosf(rotDegree);

        //rotDegree = ConvertDegree(rotDegree);

        //pos += dest * (100.0f * Time::DeltaTime());

        //tr->SetPosition(pos);

        //if (mTime > 3.0f)
        //{
        //    mState = CatScript::eState::Walk;
        //    int direction = (rand() % 4);
        //    mDirection = (eDirection)direction;
        //    playWalkAnimationByDirection(mDirection);
        //    mTime = 0.0f;
        //}
    }

    void CatScript::move()
    {
        mTime += Time::DeltaTime();
        if (mTime > 2.0f)
        {
            int isLayDown = rand() % 2;
            if (isLayDown)
            {
                mState = eState::LayDown;
                mAnimator->PlayAnimation(L"LayDown", false);
            }
            else
            {
                mState = eState::SitDown;
                mAnimator->PlayAnimation(L"SitDown", false);
            }
        }

        Transform* tr = GetOwner()->GetComponent<Transform>();
        translate(tr);
    }

    void CatScript::layDown()
    {

    }

    void CatScript::playWalkAnimationByDirection(eDirection dir)
    {
        switch (dir)
        {
        case CatScript::eDirection::Left:
            mAnimator->PlayAnimation(L"LeftWalk", true);
            break;
        case CatScript::eDirection::Right:
            mAnimator->PlayAnimation(L"RightWalk", true);
            break;
        case CatScript::eDirection::Down:
            mAnimator->PlayAnimation(L"DownWalk", true);
            break;
        case CatScript::eDirection::Up:
            mAnimator->PlayAnimation(L"UpWalk", true);
            break;
        default:
            assert(false);
            break;
        }
    }
    void CatScript::translate(Transform* tr)
    {
        Vector2 pos = tr->GetPosition();
        switch (mDirection)
        {
        case CatScript::eDirection::Left:
            pos.x -= 100.0f * Time::DeltaTime();
            break;
        case CatScript::eDirection::Right:
            pos.x += 100.0f * Time::DeltaTime();
            break;
        case CatScript::eDirection::Down:
            pos.y += 100.0f * Time::DeltaTime();
            break;
        case CatScript::eDirection::Up:
            pos.y -= 100.0f * Time::DeltaTime();
            break;
        default:
            assert(false);
            break;
        }
        tr->SetPosition(pos);
    }
}