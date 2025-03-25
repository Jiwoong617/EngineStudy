#pragma once
#include "jwComponent.h"
#include "jwAnimation.h"

namespace jw
{
    class Animator : public Component
    {
    public:
        Animator();
        ~Animator();

        void Initialize() override;
        void Update()  override;
        void LateUpdate()  override;
        void Render(HDC hdc)  override;

        void CreateAnimation(const std::wstring& name
            , graphics::Texture* spriteSheet
            , Vector2 leftTop   //시작 위치
            , Vector2 size      //스프라이트 사이즈
            , Vector2 offset    //애니메이션 오프셋(피벗)
            , UINT spriteLegth  //몇 장 자를건지
            , float duration);  //애니메이션 재생 속도

        Animation* FindAnimation(const std::wstring& name);
        //전달 인자를 읽어 올때, 오른쪽부터 읽어옴
        // - 왼쪽을 초기화했는데 오른쪽을 초기화 안하면 오류남
        void PlayAnimation(const std::wstring& name, bool loop = true);

    private:
        std::map<std::wstring, Animation*> mAnimations;
        Animation* mActiveAnimation;
        bool mbLoop;
    };
}