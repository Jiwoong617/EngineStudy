#pragma once
#include "jwComponent.h"
#include "jwAnimation.h"

namespace jw
{
    class Animator : public Component
    {
    public:
        struct Event
        {
            //간편하게 넣기
            void operator=(std::function<void()> func)
            {
                mEvent = std::move(func);
            }

            void operator()() //함수처럼 쓰고 싶을 때
            {
                if (mEvent) //있으면 실행
                    mEvent();
            }

            std::function<void()> mEvent;
        };

        struct Events
        {
            Event startEvent;
            Event completeEvent;
            Event endEvent;
        };

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

        void CreateAnimationByFolder(const std::wstring& name
            , const std::wstring& path
            , Vector2 offset, float duration);

        Animation* FindAnimation(const std::wstring& name);
        //전달 인자를 읽어 올때, 오른쪽부터 읽어옴
        // - 왼쪽을 초기화했는데 오른쪽을 초기화 안하면 오류남
        void PlayAnimation(const std::wstring& name, bool loop = true);


        Events* FindEvents(const std::wstring& name);
        std::function<void()>& GetStartEvent(const std::wstring& name);
        std::function<void()>& GetCompleteEvent(const std::wstring& name);
        std::function<void()>& GetEndEvent(const std::wstring& name);

        bool IsComplete() { return mActiveAnimation->IsComplete(); }

    private:
        std::map<std::wstring, Animation*> mAnimations;
        Animation* mActiveAnimation;
        bool mbLoop;

        //Event
        std::map<std::wstring, Events*> mEvents;
    };
}