#pragma once

#include <core/Types.h>
#include <dsp/Types.h>

namespace Core::Api
{
  using Step = uint8_t;

  class Interface
  {
   public:
    virtual ~Interface() = default;

    virtual void setParameter(TileId tileId, ParameterId parameterId, const ParameterValue &value) = 0;
    virtual void incParameter(TileId tileId, ParameterId parameterId, int steps) = 0;
    [[nodiscard]] virtual ParameterValue getParameter(TileId tileId, ParameterId parameterId) const = 0;

    [[nodiscard]] virtual Dsp::SharedSampleBuffer getSamples(TileId tileId) const = 0;
    [[nodiscard]] std::vector<TileId> getSelectedTiles() const;

    // Convenience
    ParameterValue getFirstSelectedTileParameter(ParameterId parameterId) const;
    [[nodiscard]] Step loopPositionToStep(Dsp::FramePos pos) const;
    [[nodiscard]] Pattern getMergedPattern() const;
    void incSelectedTilesParameter(ParameterId parameterId, int steps);
    void toggleSelectedTilesParameter(ParameterId parameterId);

    void setStep(Step step, bool value);
  };
}
