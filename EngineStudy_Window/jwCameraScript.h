#pragma once
#include "..\\EngineStudy_Source\\jwScript.h"
#include "..\\EngineStudy_Source\\jwTransform.h"

namespace jw
{
    class CameraScript : public Script
    {
    public:
        CameraScript();
        ~CameraScript();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC hdc) override;

    private:

    };
}