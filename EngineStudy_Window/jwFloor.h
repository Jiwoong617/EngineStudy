#pragma once
#include "..\\EngineStudy_Source\\jwGameObject.h"

namespace jw
{
    class Floor : public GameObject
    {
    public:
        Floor();
        ~Floor();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC hdc) override;

    private:

    };
}