#pragma once
#include "jwComponent.h"


namespace jw
{
    class Script : public Component
    {
    public:
        Script();
        ~Script();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC hdc) override;

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);
        virtual void OnCollisionExit(class Collider* other);

    private:

    };
}