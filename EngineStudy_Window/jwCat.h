#pragma once
#include "..\\EngineStudy_Source\\jwGameObject.h"


namespace jw
{

    class Cat : public GameObject
    {
    public:
        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC hdc) override;

    private:

    };
}