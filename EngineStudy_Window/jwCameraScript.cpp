#include "jwCameraScript.h"
#include "jwInput.h"
#include "jwTransform.h"
#include "jwTime.h"
#include "jwGameObject.h"
#include "jwAnimator.h"
#include "jwCat.h"
#include "jwCatScript.h"
#include "jwObject.h"
#include "jwResources.h"

namespace jw
{
    CameraScript::CameraScript()
    {
    }
    CameraScript::~CameraScript()
    {
    }

    void CameraScript::Initialize()
    {
    }

    void CameraScript::Update()
    {
        Transform* tr = GetOwner()->GetComponent<Transform>();
        Vector2 pos = tr->GetPosition();

        if (Input::GetKey(eKeyCode::Right))
            pos.x += 100.0f * Time::DeltaTime();
        if (Input::GetKey(eKeyCode::Left))
            pos.x -= 100.0f * Time::DeltaTime();
        if (Input::GetKey(eKeyCode::Up))
            pos.y -= 100.0f * Time::DeltaTime();
        if (Input::GetKey(eKeyCode::Down))
            pos.y += 100.0f * Time::DeltaTime();

        tr->SetPosition(pos);
    }

    void CameraScript::LateUpdate()
    {
    }

    void CameraScript::Render(HDC hdc)
    {
    }
}