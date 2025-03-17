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
		if (Input::GetKey(eKeyCode::A)) //0x8000 : 키가 눌려있을 때
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
		//빨강 브러쉬 생성
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
		//브러쉬 선택 및 이전 브러쉬(기본 - 하양) 저장
		HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, brush);

		HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
		HPEN oldpen = (HPEN)SelectObject(hdc, pen);

		Rectangle(hdc, 100 + mX, 100 + mY, 200 + mX, 200 + mY);

		//다시 하얀색으로 선택
		SelectObject(hdc, oldbrush);
		SelectObject(hdc, oldpen);
		//매 프레임 마다 힙에 할당되는 파란 브러쉬 삭제
		DeleteObject(brush);
		DeleteObject(pen);
	}
}