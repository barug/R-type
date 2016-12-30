//
// rtype
//

# include       <iostream>
# include       "RTypeUI.hpp"

RTypeUI::RTypeUI(IGui &gui) : _gui(gui),
                              _timer(new Timer),
                              _context(RTypeUI::Context::Game)
{}

RTypeUI::~RTypeUI()
{}

void                    RTypeUI::setContext(const RTypeUI::Context context)
{
  _context = context;
}

RTypeUI::Context        RTypeUI::getContext(void) const
{
  return _context;
}

void                    RTypeUI::displayIntroduction(void)
{
  static unsigned int   i = 0;

  if (i < 255)
    i += 10;
  _gui.setTextureAt("./assets/sprites/background.jpg", 0, 0, 1.);
  _gui.fillRec(0, 0, 800, 600, 0x000000, i);
  if (i >= 254)
    {
      _gui.setTextureAt("./assets/sprites/rtype-logo.png", 180, 40, 1.);
      if (_gui.magnetTile(_gui.getMouseX(), _gui.getMouseY(), 380, 300, 40, 40))
        {
          if (_gui.buttonLeftIsClicked())
            {
              i = 0;
              _context = Context::Authentification;
              _timer->setState(Timer::State::NONE);
            }
          else
            _gui.writeAt("> START", 340, 300, 0x00ff00, 1.2);
        }
      else
        _gui.writeAt("START", 350, 300, 0xc60000, 1.2);
      if (_gui.getKey() == IGui::Key::ENTER)
        {
          _context = Context::Authentification;
          _timer->setState(Timer::State::NONE);
        }
    }
}

void                    RTypeUI::displayAuthentification(std::string *ip, unsigned int *port)
{
  static bool           ipIsSet = false;
  static bool           tabSwitchAvailable = false;
  static std::string    ipSet;
  static std::string    portSet;

  _gui.setTextureAt("./assets/sprites/background.jpg", 0, 0, 1.);
  _gui.setTextureAt("./assets/sprites/rtype-logo.png", 180, 40, 1.);
  _gui.writeAt("IP :", 200, 200, 0xffffff, 1.);
  _gui.writeAt("PORT :", 160, 300, 0xffffff, 1.);
  _gui.writeAt("tab to switch and enter for done..", 800/2 - 100, 380, 0xffffff, 0.5);

  if (_gui.getKey() == IGui::Key::TAB)
    {
      if (_timer->timerIn(200))
        tabSwitchAvailable = false;
      else
        {
          tabSwitchAvailable = true;
          _timer->setState(Timer::State::NONE);
        }
    }

  if (!ipIsSet)
    {
      // selection for ipSet
      _gui.fillRec(250, 200, 300, 50, 0xffffff, 200);
      _gui.fillRec(250, 300, 300, 50, 0xffffff, 150);

      if (ipSet != _gui.getCurrentInputBuffer())
        ipSet = _gui.getCurrentInputBuffer();

      _gui.writeAt(ipSet, 400-(ipSet.size()*4), 205, 0xffffff, 1.);
      _gui.writeAt(portSet, 370, 305, 0xffffff, 1.);

      if (_gui.getKey() == IGui::Key::ENTER)
        {
          ipSet = _gui.getCurrentInputBuffer();
          _gui.setCurrentInputBuffer("");
          if (portSet.size() && ipSet.size())
            {
              *ip = ipSet;
              *port = std::atoi(portSet.c_str());
              _context = RTypeUI::Context::Loading;
              _timer->setState(Timer::State::NONE);
            }
          if (!ipSet.empty())
            ipIsSet = true;
        }
      else if (_gui.getKey() == IGui::Key::TAB && tabSwitchAvailable)
        {
          ipSet = _gui.getCurrentInputBuffer();
          _gui.setCurrentInputBuffer("");
          ipIsSet = true;
        }
    }

  else
    {
      // selection for portSet
      _gui.fillRec(250, 200, 300, 50, 0xffffff, 150);
      _gui.fillRec(250, 300, 300, 50, 0xffffff, 200);

      if (portSet != _gui.getCurrentInputBuffer())
        portSet = _gui.getCurrentInputBuffer();
      _gui.writeAt(ipSet, 350, 205, 0xffffff, 1.);
      _gui.writeAt(portSet, 370, 305, 0xffffff, 1.);

      if (_gui.getKey() == IGui::Key::ENTER)
        {
          portSet = _gui.getCurrentInputBuffer();
          _gui.setCurrentInputBuffer("");
          if (portSet.size() && ipSet.size())
            {
              *ip = ipSet;
              *port = std::atoi(portSet.c_str());
              _context = RTypeUI::Context::Loading;
              _timer->setState(Timer::State::NONE);
            }
        }
      else if (_gui.getKey() == IGui::Key::TAB && tabSwitchAvailable)
        {
          portSet = _gui.getCurrentInputBuffer();
          _gui.setCurrentInputBuffer("");
          ipIsSet = false;
        }
    }
}

void                    RTypeUI::displayLoading(void)
{
  std::string           displayDot;

  if (_timer->timerIn(500))
    {
      for (unsigned int i = 0; i < _timer->timeLeft() / 100 && i < 3; i++)
        displayDot += ".";
      _gui.setTextureAt("./assets/sprites/background.jpg", 0, 0, 1.);
      _gui.setTextureAt("./assets/sprites/rtype-logo.png", 180, 40, 1.);
      _gui.fillRec(0, 0, 800, 600, 0x000000, 180);
      _gui.writeAt("loading" + displayDot, (800/2) - 50, (600/2) - 50, 0x00ff00, 1.2);
    }
  else
    {
      _timer->setState(Timer::State::NONE);
      _context = RTypeUI::Context::WaitingRoom;
    }
}

void                    RTypeUI::displayWaitingRoom(void)
{
  _gui.setTextureAt("./assets/sprites/background.jpg", 0, 0, 1.);
  _gui.fillRec(0, 0, 800, 600, 0x000000, 180);
  _gui.writeAt("Waiting Room", 300, 30, 0x00ff00, 1.2);
  _context = RTypeUI::Context::Game;
}

void                    RTypeUI::displayGame(void)
{
  static int            firstImageSpaceX = 0;
  static int            secondImageSpaceX = 800;

  if (firstImageSpaceX == -800)
    firstImageSpaceX = 0;
  if (secondImageSpaceX == 0)
    secondImageSpaceX = 800;
  _gui.setTextureAt("./assets/sprites/rtype-space.png", firstImageSpaceX-=2, 0, 1.);
  _gui.setTextureAt("./assets/sprites/rtype-space.png", secondImageSpaceX-=2, 0, 1.);
}

void                    RTypeUI::displayMenu(void)
{
  _gui.setTextureAt("./assets/sprites/background.jpg", 0, 0, 1.);
  _gui.fillRec(0, 0, 800, 600, 0x000000, 180);
}
