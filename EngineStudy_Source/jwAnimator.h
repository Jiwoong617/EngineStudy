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
            //�����ϰ� �ֱ�
            void operator=(std::function<void()> func)
            {
                mEvent = std::move(func);
            }

            void operator()() //�Լ�ó�� ���� ���� ��
            {
                if (mEvent) //������ ����
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
            , Vector2 leftTop   //���� ��ġ
            , Vector2 size      //��������Ʈ ������
            , Vector2 offset    //�ִϸ��̼� ������(�ǹ�)
            , UINT spriteLegth  //�� �� �ڸ�����
            , float duration);  //�ִϸ��̼� ��� �ӵ�

        void CreateAnimationByFolder(const std::wstring& name
            , const std::wstring& path
            , Vector2 offset, float duration);

        Animation* FindAnimation(const std::wstring& name);
        //���� ���ڸ� �о� �ö�, �����ʺ��� �о��
        // - ������ �ʱ�ȭ�ߴµ� �������� �ʱ�ȭ ���ϸ� ������
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