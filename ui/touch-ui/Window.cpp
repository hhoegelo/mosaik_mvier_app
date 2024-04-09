#include "Window.h"
#include "ui/touch-ui/tiles/Tiles.h"
#include "ui/touch-ui/toolbox/Toolboxes.h"
#include <gtkmm/grid.h>

namespace Ui::Touch
{
  auto css = R"(
    .has-steps-indicator{
        background-color: rgb(40,40,40);
        margin: 3px;
    }

    .has-steps-indicator.has-steps {
        background-color: rgb(90,90,90);
    }

    .is-playing-indicator {
        margin: 3px;
    }

    .is-playing-indicator.is-playing {
        background-color: rgb(40,40,40);
    }

  .tile .volume {
    min-height: 2cm;
  }

  .waveform {
    min-height: 3cm;
    min-width: 3cm;
  }

    .tile {
        border: 1px solid black;
        border-radius: 0px;
        margin: 2px;
    }

    .tile.selected {
        border-color: rgb(160, 160, 160);
    }

  .is-playing-indicator.level-80db {
    background: rgba(255, 0, 0, 0);
  }
.is-playing-indicator.level-70db {
    background: rgba(255, 0, 0, 0.3);
  }
.is-playing-indicator.level-60db {
    background: rgba(255, 0, 0, 0.4);
  }
.is-playing-indicator.level-50db {
    background: rgba(255, 0, 0, 0.5);
  }
.is-playing-indicator.level-40db {
    background: rgba(255, 0, 0, 0.6);
  }
.is-playing-indicator.level-30db {
    background: rgba(255, 0, 0, 0.7);
  }
.is-playing-indicator.level-20db {
    background: rgba(255, 0, 0, 0.8);
  }
.is-playing-indicator.level-10db {
    background: rgba(255, 0, 0, 0.9);
  }
.is-playing-indicator.level-0db {
    background: rgba(255, 0, 0, 1.0);
  }

.section .header {
	border: 1px solid black;
	background: gray;
	color: white;
	font-size: xx-large;
	font-weight: bold;
}

.waveform {
	min-height: 200px;
}
  )";

  Window::Window(Core::Api::Interface& core, Dsp::Api::Display::Interface& dsp)
      : m_core(core)
      , m_dsp(dsp)
  {
    build();
  }

  Window::~Window() = default;

  void Window::build()
  {
    auto cssProvider = Gtk::CssProvider::create();
    cssProvider->load_from_data(css);
    Glib::RefPtr<Gtk::StyleContext> styleContext = Gtk::StyleContext::create();
    styleContext->add_provider_for_screen(Gdk::Screen::get_default(), cssProvider,
                                          GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    set_title("Mosaik");
    set_border_width(10);
    auto box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL));

    m_tiles = new Tiles(m_core, m_dsp);
    box->pack_start(*m_tiles, false, false);

    m_toolboxes = new Toolboxes(m_core);
    box->pack_start(*m_toolboxes, true, true);

    add(*box);
    show_all();
  }

  Ui::Toolboxes Window::getSelectedToolbox() const
  {
    return m_toolboxes->getSelectedToolbox();
  }

  Touch::Interface::Waveform& Window::getWaveform() const
  {
    return m_toolboxes->getWaveform();
  }

  Touch::Interface::FileBrowser& Window::getFileBrowser() const
  {
    return m_toolboxes->getFileBrowser();
  }

}
