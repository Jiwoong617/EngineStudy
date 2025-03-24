#pragma once
#include "jwEntity.h"


namespace jw
{
    // virtual �Լ��� 0�� ������ �߻� Ŭ����
    // - �޸� �Ҵ� X ��ӹ޾Ƽ��� ����ؾ� ��
    class Resource abstract : public Entity 
    {
    public:
        Resource(enums::eResourceType type);
        virtual ~Resource();

        // ���������Լ� �����޸� �Ҵ��� �Ұ��������� ����
        virtual HRESULT Load(const std::wstring& path) = 0; 

        const std::wstring& GetPath() { return mPath; }
        void SetPath(const std::wstring& path) { mPath = path; }

    private:
        const enums::eResourceType mType;
        std::wstring mPath;
    };

 }