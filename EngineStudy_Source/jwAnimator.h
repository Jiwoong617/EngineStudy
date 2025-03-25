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
            , Vector2 leftTop   //���� ��ġ
            , Vector2 size      //��������Ʈ ������
            , Vector2 offset    //�ִϸ��̼� ������(�ǹ�)
            , UINT spriteLegth  //�� �� �ڸ�����
            , float duration);  //�ִϸ��̼� ��� �ӵ�

        Animation* FindAnimation(const std::wstring& name);
        //���� ���ڸ� �о� �ö�, �����ʺ��� �о��
        // - ������ �ʱ�ȭ�ߴµ� �������� �ʱ�ȭ ���ϸ� ������
        void PlayAnimation(const std::wstring& name, bool loop = true);

    private:
        std::map<std::wstring, Animation*> mAnimations;
        Animation* mActiveAnimation;
        bool mbLoop;
    };
}