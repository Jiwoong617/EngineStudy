#pragma once
#include "..\\EngineStudy_Source\\jwScript.h"


namespace jw
{
    class PlayerScript : public Script
    {
    public:
        PlayerScript();
        ~PlayerScript();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC hdc) override;


    private:

    };
}