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
        //�� = ���� * ���ӵ� (f = ma)
        mAccelation = mForce / mMass;

		//�ӵ� += ���ӵ� * �ð�
        mVelocity += mAccelation * Time::DeltaTime();

        if (mbGround)
        {
            //���� ���� ��
            Vector2 gravity = mGravity;
            gravity.normalize();

            float dot = Vector2::Dot(mVelocity, gravity);
            //�߷� * ���� �̵��� ����(����)
            mVelocity -= gravity * dot;
        }
        else
        {
            mVelocity += mGravity * Time::DeltaTime();
        }

        //�ִ� �ӵ� ����
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


        //������ ����
        if (!(mVelocity == Vector2::Zero))
        {
            //������ - �ӵ��� �ݴ�
            Vector2 friction = -mVelocity;
            friction = friction.normalize() * mFriction * mMass * Time::DeltaTime();

			//�������� ũ�Ⱑ �ӵ����� ũ�� ���߰�, �ƴϸ� ���ؼ� ����
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