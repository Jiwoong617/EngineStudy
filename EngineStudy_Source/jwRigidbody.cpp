#include "jwRigidbody.h"
#include "jwTime.h"
#include "jwTransform.h"
#include "jwGameObject.h"

namespace jw
{
    Rigidbody::Rigidbody()
        : Component(enums::eComponentType::Rigidbody)
		, mbGround(false)
        , mMass(1.0f)
        , mFriction(10.0f)
        , mForce(Vector2::Zero)
        , mVelocity(Vector2::Zero)
        , mGravity(Vector2(0.0f, 800.0f))
        , mAccelation(Vector2::Zero)
        , mLimitedVelocity(Vector2(200.0f, 1000.0f))
    {

    }
    Rigidbody::~Rigidbody()
    {
    }

    void Rigidbody::Initialize()
    {
    }

    void Rigidbody::Update()
    {
        //힘 = 질량 * 가속도 (f = ma)
        mAccelation = mForce / mMass;

		//속도 += 가속도 * 시간
        mVelocity += mAccelation * Time::DeltaTime();

        if (mbGround)
        {
            //땅에 있을 때
            Vector2 gravity = mGravity;
            gravity.normalize();

            float dot = Vector2::Dot(mVelocity, gravity);
            //중력 * 내가 이동한 길이(내적)
            mVelocity -= gravity * dot;
        }
        else
        {
            mVelocity += mGravity * Time::DeltaTime();
        }

        //최대 속도 제한
        Vector2 gravity = mGravity;
        gravity.normalize();
        float dot = Vector2::Dot(mVelocity, gravity);
        gravity = gravity * dot;

        Vector2 sideVelocity = mVelocity - gravity;
        if (mLimitedVelocity.y < gravity.length())
        {
            gravity.normalize();
            gravity *= mLimitedVelocity.y;
        }

        if (mLimitedVelocity.x < sideVelocity.length())
        {
            sideVelocity.normalize();
            sideVelocity *= mLimitedVelocity.x;
        }
        mVelocity = gravity + sideVelocity;


        //마찰력 적용
        if (!(mVelocity == Vector2::Zero))
        {
            //마찰력 - 속도의 반대
            Vector2 friction = -mVelocity;
            friction = friction.normalize() * mFriction * mMass * Time::DeltaTime();

			//마찰력의 크기가 속도보다 크면 멈추고, 아니면 더해서 감속
            if (mVelocity.length() <= friction.length())
                mVelocity = Vector2::Zero;
            else
                mVelocity += friction;
        }

        Transform* tr = GetOwner()->GetComponent<Transform>();
        Vector2 pos = tr->GetPosition();
        pos = pos + mVelocity * Time::DeltaTime();
        tr->SetPosition(pos);

        mForce.clear();
    }

    void Rigidbody::LateUpdate()
    {
    }

    void Rigidbody::Render(HDC hdc)
    {
    }
}