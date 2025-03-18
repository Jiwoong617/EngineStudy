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

        //빨강 브러쉬 생성
        HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
        //브러쉬 선택 및 이전 브러쉬(기본 - 하양) 저장
        HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, brush);

        HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
        HPEN oldpen = (HPEN)SelectObject(hdc, pen);

        Transform* tr = GetOwner()->GetComponent<Transform>();
        Rectangle(hdc, tr->GetX(), tr->GetY(), 100 + tr->GetX(), 100 + tr->GetY());

        //다시 하얀색으로 선택
        SelectObject(hdc, oldbrush);
        SelectObject(hdc, oldpen);
        //매 프레임 마다 힙에 할당되는 파란 브러쉬 삭제
        DeleteObject(brush);
        DeleteObject(pen);
    }
}