#pragma once

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/box.h>
#include "ui/touch-ui/sections/SectionWrapper.h"
#include "ui/Types.h"
#include "ui/touch-ui/Interface.h"

namespace Core::Api
{
  class Interface;
}

namespace Ui::Touch
{
  class Waveform;
  class GlobalTools;
  class TileTools;
  class Steps;

  class Toolboxes : public SectionWrapper<Section::Toolboxes, Gtk::Box>, public ToolboxesInterface
  {
   public:
    Toolboxes(Touch::Interface &touch, Core::Api::Interface &core);

    WaveformInterface &getWaveform() const override;
    FileBrowserInterface &getFileBrowser() const override;
    Toolbox getSelectedToolbox() const override;

   private:
    Core::Api::Interface &m_core;

    Tools::ReactiveVar<::Ui::Toolbox> m_selectedToolbox;
    Gtk::Box &m_box;
    TileTools &m_tileTools;
    WaveformInterface &m_waveform;
  };
}
