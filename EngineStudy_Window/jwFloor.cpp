#include "jwFloor.h"
#include "jwCat.h"
#include "jwInput.h"
#include "jwTransform.h"
#include "jwTime.h"

namespace jw
{
    Floor::Floor()
    {
    }
    Floor::~Floor()
    {
    }

    void Floor::Initialize()
    {
        GameObject::Initialize();
    }

    void Floor::Update()
    {
        GameObject::Update();
    }

    void Floor::LateUpdate()
    {
        GameObject::LateUpdate();
    }

    void Floor::Render(HDC hdc)
    {
        GameObject::Render(hdc);
    }
}