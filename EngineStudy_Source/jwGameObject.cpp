#include "jwGameObject.h"


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

		if (GetAsyncKeyState(VK_LEFT) & 0x8000) //0x8000 : 키가 눌려있을 때
		{
			mX -= 0.01f;
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			mX += 0.01f;
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			mY -= 0.01f;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			mY += 0.01f;
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