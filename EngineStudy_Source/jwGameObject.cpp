#include "jwGameObject.h"
#include "jwInput.h"
#include "jwTime.h"

namespace jw
{
	GameObject::GameObject()
		: mX(0)
		, mY(0)
	{
	}
	GameObject::~GameObject()
	{
	}

	void GameObject::Update()
	{
		const int speed = 100;
		if (Input::GetKey(eKeyCode::A)) //0x8000 : Ű�� �������� ��
		{
			mX -= speed * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::D))
		{
			mX += speed * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::W))
		{
			mY -= speed * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::S))
		{
			speed* Time::DeltaTime();
		}
	}

	void GameObject::LateUpdate()
	{
	}

	void GameObject::Render(HDC hdc)
	{
		//���� �귯�� ����
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
		//�귯�� ���� �� ���� �귯��(�⺻ - �Ͼ�) ����
		HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, brush);

		HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
		HPEN oldpen = (HPEN)SelectObject(hdc, pen);

		Rectangle(hdc, 100 + mX, 100 + mY, 200 + mX, 200 + mY);

		//�ٽ� �Ͼ������ ����
		SelectObject(hdc, oldbrush);
		SelectObject(hdc, oldpen);
		//�� ������ ���� ���� �Ҵ�Ǵ� �Ķ� �귯�� ����
		DeleteObject(brush);
		DeleteObject(pen);
	}
}