#include "jwAudioListener.h"
#include "jwTransform.h"
#include "jwGameObject.h"
#include "jwFmod.h"

namespace jw
{
    AudioListener::AudioListener()
        : Component(eComponentType::AudioListener)
    {
    }
    AudioListener::~AudioListener()
    {
    }

    void AudioListener::Initialize()
    {
    }

    void AudioListener::Update()
    {
    }

    void AudioListener::LateUpdate()
    {
        Transform* tr = GetOwner()->GetComponent<Transform>();
        Vector2 pos = tr->GetPosition();

        Fmod::Set3DListenerAttributes(&pos);
    }

    void AudioListener::Render(HDC hdc)
    {
    }

}