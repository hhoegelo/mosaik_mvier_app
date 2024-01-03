#pragma once

namespace Core
{
  namespace Api
  {
    class Interface;
  }
}

namespace Dsp
{
  namespace Api
  {
    namespace Display
    {
      class Interface;
    }
  }
}

namespace Ui
{
  namespace Touch
  {
    class Ui
    {
     public:
      Ui(Core::Api::Interface &core, Dsp::Api::Display::Interface &dsp);

      void run();

     private:
      Core::Api::Interface &m_core;
      Dsp::Api::Display::Interface &m_dsp;
    };
  }
}
