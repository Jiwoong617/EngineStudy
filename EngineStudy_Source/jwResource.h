#pragma once
#include "jwEntity.h"


namespace jw
{
    // virtual 함수에 0이 붙으면 추상 클래스
    // - 메모리 할당 X 상속받아서만 사용해야 됨
    class Resource abstract : public Entity 
    {
    public:
        Resource(enums::eResourceType type);
        virtual ~Resource();

        // 순수가상함수 실제메모리 할당이 불가능해지는 문법
        virtual HRESULT Load(const std::wstring& path) = 0; 

        const std::wstring& GetPath() { return mPath; }
        void SetPath(const std::wstring& path) { mPath = path; }

    private:
        const enums::eResourceType mType;
        std::wstring mPath;
    };

 }