#include "jwSpriteRenderer.h"
#include "jwGameObject.h"
#include "jwTransform.h"

namespace jw
{
    SpriteRenderer::SpriteRenderer()
    {
    }
    SpriteRenderer::~SpriteRenderer()
    {
    }
    void SpriteRenderer::Initialize()
    {
    }
    void SpriteRenderer::Update()
    {
    }
    void SpriteRenderer::LateUpdate()
    {
    }

    void SpriteRenderer::Render(HDC hdc)
    {

        //���� �귯�� ����
        HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
        //�귯�� ���� �� ���� �귯��(�⺻ - �Ͼ�) ����
        HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, brush);

        HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
        HPEN oldpen = (HPEN)SelectObject(hdc, pen);

        Transform* tr = GetOwner()->GetComponent<Transform>();
        Rectangle(hdc, tr->GetX(), tr->GetY(), 100 + tr->GetX(), 100 + tr->GetY());

        //�ٽ� �Ͼ������ ����
        SelectObject(hdc, oldbrush);
        SelectObject(hdc, oldpen);
        //�� ������ ���� ���� �Ҵ�Ǵ� �Ķ� �귯�� ����
        DeleteObject(brush);
        DeleteObject(pen);
    }
}