#pragma once

#include "Types.h"
#include "AudioKernel.h"
#include <limits>

namespace Dsp
{
  class Tile
  {
   public:
    struct ToUi
    {
      float levelLeft { 0.0f };
      float levelRight { 0.0f };
      FramePos frame { 0 };
    };

    void doAudio(Busses &busses, const AudioKernel::Tile &kernel, ToUi &ui, FramePos currentLoopPosition);

   private:
    float doEnvelope(const AudioKernel::Tile &kernel, FramePos iFramePos) const;
    StereoFrame doPlayground(const StereoFrame &input, float playgroundParam1, float playgroundParam2,
                             float playgroundParam3, float playgroundParam4, float playgroundParam5,
                             float playgroundParam6, float playgroundParam7);

    static constexpr auto c_invalidFramePosF32 = std::numeric_limits<float>::max();
    static constexpr auto c_invalidFramePosU64 = std::numeric_limits<FramePos>::max();

    float m_gainLeft { 1.0f };
    float m_gainRight { 1.0f };
    float m_framePosition = c_invalidFramePosF32;

    float m_reverbSend { 0.0f };

    // playground dsp state goes here
    float m_smoothedPlaygroundSomething { 0.0f };
    float m_smoothedPlaygroundOtherThing { 0.0f };

    float m_HPz { 0.0f };
    float m_BPz { 0.0f };
    float m_LPz { 0.0f };
  };
}
