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

		if (GetAsyncKeyState(VK_LEFT) & 0x8000) //0x8000 : Ű�� �������� ��
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