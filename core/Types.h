#pragma once

#include <tools/Format.h>
#include <dsp/Types.h>
#include <filesystem>
#include <variant>
#include <optional>
#include <vector>
#include <cmath>

namespace Core
{
  enum WizardMode
  {
    Or = 0,
    And = 1,
    Replace = 2,
    Not = 3

  };
  enum class ParameterId
  {
    // Globals
    GlobalTempo,
    GlobalVolume,

    // Per Tile
    Selected,
    SampleFile,
    Shuffle,
    Pattern,
    Balance,
    Gain,
    Mute,
    Reverse,
    EnvelopeFadeInPos,
    EnvelopeFadedInPos,
    EnvelopeFadeOutPos,
    EnvelopeFadedOutPos,
    TriggerFrame,
    Speed,

    // Wizard
    WizardMode,
    WizardRotate,
    WizardOns,
    WizardOffs,
  };

  using Path = std::filesystem::path;
  using Pattern = std::array<bool, NUM_STEPS>;
  using Float = float;
  using Bool = bool;
  using TileId = std::optional<uint32_t>;
  using FramePos = int64_t;

  using ParameterValue = std::variant<Bool, Float, Path, Pattern, FramePos, uint8_t>;

  template <ParameterId id> struct ParameterDescription;

  template <> struct ParameterDescription<ParameterId::GlobalTempo>
  {
    constexpr static ParameterId id = ParameterId::GlobalTempo;
    constexpr static auto name = "tempo";
    using Type = Float;
    constexpr static Type min = 20.0f;
    constexpr static Type max = 400.0f;
    constexpr static Type coarse = 1.0f;
    constexpr static auto unit = "bpm";

    static std::string format(Type t)
    {
      return Tools::format("%3.1f %s", t, unit);
    }
  };

  template <> struct ParameterDescription<ParameterId::GlobalVolume>
  {
    constexpr static ParameterId id = ParameterId::GlobalVolume;
    constexpr static auto name = "volume";
    using Type = Float;
    constexpr static Type min = -72.0f;
    constexpr static Type max = 0.0f;
    constexpr static Type coarse = 0.5f;
    constexpr static auto unit = "dB";

    static std::string format(Type t)
    {
      return Tools::format("%2.1f %s", t, unit);
    }
  };

  template <> struct ParameterDescription<ParameterId::Selected>
  {
    constexpr static ParameterId id = ParameterId::Selected;
    using Type = Bool;
    constexpr static auto name = "selected";

    static std::string format(Type t)
    {
      return Tools::format("%s", t ? "yes" : "no");
    }
  };

  template <> struct ParameterDescription<ParameterId::Reverse>
  {
    constexpr static ParameterId id = ParameterId::Reverse;
    using Type = Bool;
    constexpr static auto name = "reverse";

    static std::string format(Type t)
    {
      return Tools::format("%s", t ? "<<<" : ">>>");
    }
  };

  template <> struct ParameterDescription<ParameterId::SampleFile>
  {
    constexpr static ParameterId id = ParameterId::SampleFile;
    using Type = Path;
    constexpr static auto name = "sample";

    static std::string format(const Type& t)
    {
      return t.string();
    }
  };

  template <> struct ParameterDescription<ParameterId::Pattern>
  {
    constexpr static ParameterId id = ParameterId::Pattern;
    using Type = Pattern;
    constexpr static auto name = "pattern";

    static std::string format(const Type& t)
    {
      return "n/a";
    }
  };

  template <> struct ParameterDescription<ParameterId::Mute>
  {
    constexpr static ParameterId id = ParameterId::Mute;
    using Type = Bool;
    constexpr static auto name = "mute";

    static std::string format(const Type& t)
    {
      return Tools::format("%s", t ? "muted" : "unmuted");
    }
  };

  template <> struct ParameterDescription<ParameterId::Balance>
  {
    constexpr static ParameterId id = ParameterId::Balance;
    constexpr static auto name = "balance";
    using Type = Float;
    constexpr static Type min = -1.0f;
    constexpr static Type max = 1.0f;
    constexpr static Type coarse = 0.01f;
    constexpr static auto unit = "%";

    static std::string format(Type t)
    {
      return Tools::format("%3.2f %s", 100 * t, unit);
    }
  };

  template <> struct ParameterDescription<ParameterId::Gain>
  {
    constexpr static ParameterId id = ParameterId::Gain;
    constexpr static auto name = "gain";
    using Type = Float;
    constexpr static Type min = -48.0f;
    constexpr static Type max = 6.0f;
    constexpr static Type coarse = 0.1f;
    constexpr static auto unit = "dB";

    static std::string format(Type t)
    {
      return Tools::format("%3.2f %s", t, unit);
    }
  };

  template <> struct ParameterDescription<ParameterId::Speed>
  {
    constexpr static ParameterId id = ParameterId::Speed;
    constexpr static auto name = "speed";
    using Type = Float;
    constexpr static Type min = -3.0f;
    constexpr static Type max = 3.0f;
    constexpr static Type coarse = 0.01f;
    constexpr static auto unit = "%";

    static std::string format(Type t)
    {
      return Tools::format("%3.2f %s", 100.0f * std::pow(2.0f, t), unit);
    }
  };

  template <> struct ParameterDescription<ParameterId::EnvelopeFadeInPos>
  {
    constexpr static ParameterId id = ParameterId::EnvelopeFadeInPos;
    constexpr static auto name = "envelopeFadeInPos";
    using Type = FramePos;

    static std::string format(Type t)
    {
      return Tools::format("%zu", t);
    }
  };

  template <> struct ParameterDescription<ParameterId::EnvelopeFadedInPos>
  {
    constexpr static ParameterId id = ParameterId::EnvelopeFadedInPos;
    constexpr static auto name = "envelopeFadedInPos";
    using Type = FramePos;

    static std::string format(Type t)
    {
      return Tools::format("%zu", t);
    }
  };

  template <> struct ParameterDescription<ParameterId::EnvelopeFadeOutPos>
  {
    constexpr static ParameterId id = ParameterId::EnvelopeFadeOutPos;
    constexpr static auto name = "envelopeFadeOutPos";
    using Type = FramePos;

    static std::string format(Type t)
    {
      return Tools::format("%zu", t);
    }
  };

  template <> struct ParameterDescription<ParameterId::EnvelopeFadedOutPos>
  {
    constexpr static ParameterId id = ParameterId::EnvelopeFadedOutPos;
    constexpr static auto name = "envelopeFadedOutPos";
    using Type = FramePos;

    static std::string format(Type t)
    {
      return Tools::format("%zu", t);
    }
  };

  template <> struct ParameterDescription<ParameterId::TriggerFrame>
  {
    constexpr static ParameterId id = ParameterId::TriggerFrame;
    constexpr static auto name = "triggerFrame";
    using Type = FramePos;

    static std::string format(Type t)
    {
      return Tools::format("%zu", t);
    }
  };

  template <> struct ParameterDescription<ParameterId::Shuffle>
  {
    constexpr static ParameterId id = ParameterId::Shuffle;
    constexpr static auto name = "shuffle";
    using Type = Float;
    constexpr static Type min = -1.0f;
    constexpr static Type max = 1.0f;
    constexpr static Type coarse = 0.01f;
    constexpr static auto unit = "%";

    static std::string format(Type t)
    {
      return Tools::format("%3.2f %s", 100 * t, unit);
    }
  };

  template <> struct ParameterDescription<ParameterId::WizardMode>
  {
    constexpr static ParameterId id = ParameterId::WizardMode;
    constexpr static auto name = "wizardMode";
    using Type = uint8_t;

    static std::string format(Type t)
    {
      switch(static_cast<WizardMode>(t))
      {
        case Or:
          return "Or";
        case And:
          return "And";
        case Replace:
          return "Replace";
        case Not:
          return "Not";
      }
      return "n/a";
    }
  };

  template <> struct ParameterDescription<ParameterId::WizardRotate>
  {
    constexpr static ParameterId id = ParameterId::WizardRotate;
    constexpr static auto name = "wizardRotate";
    using Type = float;
    constexpr static Type min = -63.0f;
    constexpr static Type max = 63.0f;
    constexpr static Type coarse = 0.1f;

    static std::string format(Type t)
    {
      return Tools::format("%2f steps", std::round(t));
    }
  };

  template <> struct ParameterDescription<ParameterId::WizardOns>
  {
    constexpr static ParameterId id = ParameterId::WizardOns;
    constexpr static auto name = "wizardOns";
    using Type = float;
    constexpr static Type min = 0.0f;
    constexpr static Type max = 64.0f;
    constexpr static Type coarse = 0.1f;

    static std::string format(Type t)
    {
      return Tools::format("%2f steps", std::round(t));
    }
  };

  template <> struct ParameterDescription<ParameterId::WizardOffs>
  {
    constexpr static ParameterId id = ParameterId::WizardOffs;
    constexpr static auto name = "wizardOffs";
    using Type = float;
    constexpr static Type min = 0.0f;
    constexpr static Type max = 64.0f;
    constexpr static Type coarse = 0.1f;

    static std::string format(Type t)
    {
      return Tools::format("%2f steps", std::round(t));
    }
  };

  template <ParameterId... ids> struct Parameters
  {
    using Descriptors = std::tuple<ParameterDescription<ids>...>;

    static bool contains(ParameterId id)
    {
      return ((ids == id) || ...);
    }
  };

  using GlobalParameters = Parameters<ParameterId::GlobalTempo, ParameterId::GlobalVolume>;

  using TileParameters
      = Parameters<ParameterId::Selected, ParameterId::SampleFile, ParameterId::Reverse, ParameterId::Pattern,
                   ParameterId::Balance, ParameterId::Gain, ParameterId::Mute, ParameterId::Speed,
                   ParameterId::EnvelopeFadeInPos, ParameterId::EnvelopeFadedInPos, ParameterId::EnvelopeFadeOutPos,
                   ParameterId::EnvelopeFadedOutPos, ParameterId::TriggerFrame, ParameterId::Shuffle,
                   ParameterId::WizardMode, ParameterId::WizardRotate, ParameterId::WizardOns, ParameterId::WizardOffs>;
}
