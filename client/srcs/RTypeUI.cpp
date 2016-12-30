//
// rtype
//

# include       <iostream>
# include       "RTypeUI.hpp"

RTypeUI::RTypeUI(IGui &gui) : _gui(gui),
                              _timer(new Timer),
                              _context(RTypeUI::Context::Introduction)
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

  _gui.loadFont("./assets/font/breeze.ttf");
  if (i < 255)
    i += 10;
  _gui.setTextureAt("./assets/sprites/background.jpg", 0, 0, 1.);
  _gui.fillRec(0, 0, 1200, 800, 0x000000, i);
  if (i >= 254)
    {
      _gui.fillRec(500, 350, 200, 55, 0x000000, 150);
      _gui.setTextureAt("./assets/sprites/rtype-logo.png", 380, 40, 1.);
      if (_gui.magnetTile(_gui.getMouseX(), _gui.getMouseY(), 580, 400, 40, 40))
        {
          if (_gui.buttonLeftIsClicked())
            {
              i = 0;
              _context = Context::Authentification;
              _timer->setState(Timer::State::NONE);
            }
          else
            _gui.writeAt("START", 520, 355, 0xffffff, 1.2);
        }
      else
        _gui.writeAt("START", 520, 355, 0x00ff00, 1.2);
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

  _gui.loadFont("./assets/font/digital.otf");
  _gui.setTextureAt("./assets/sprites/background.jpg", 0, 0, 1.);
  _gui.setTextureAt("./assets/sprites/rtype-logo.png", 380, 40, 1.);
  _gui.writeAt("IP :", 400, 300, 0xffffff, 1.);
  _gui.writeAt("PORT :",  400 - 40, 400, 0xffffff, 1.);
  _gui.writeAt("tab to switch and enter for done..", (1200/2) - 100, 800-100, 0x000000, 0.5);

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
      _gui.fillRec(450, 300, 300, 50, 0x000000, 100);
      _gui.fillRec(450, 400, 300, 50, 0x000000, 50);

      if (ipSet != _gui.getCurrentInputBuffer())
        ipSet = _gui.getCurrentInputBuffer();

      _gui.writeAt(ipSet, (1200/2)-(ipSet.size()*4), 305, 0xffffff, 1.);
      _gui.writeAt(portSet, 570, 405, 0xffffff, 1.);

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
      if (_gui.buttonLeftIsClicked())
        if (_gui.magnetTile(_gui.getMouseX(), _gui.getMouseY(), (450 + (300/2)), 400 + 25, 40, 40))
          {
            ipSet = _gui.getCurrentInputBuffer();
            _gui.setCurrentInputBuffer("");
            ipIsSet = true;
          }
    }

  else
    {
      // selection for portSet
      _gui.fillRec(450, 300, 300, 50, 0x000000, 50);
      _gui.fillRec(450, 400, 300, 50, 0x000000, 100);

      if (portSet != _gui.getCurrentInputBuffer())
        portSet = _gui.getCurrentInputBuffer();
      _gui.writeAt(ipSet, 550, 305, 0xffffff, 1.);
      _gui.writeAt(portSet, (1200/2)-(ipSet.size()*4), 405, 0xffffff, 1.);

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
      if (_gui.buttonLeftIsClicked())
        if (_gui.magnetTile(_gui.getMouseX(), _gui.getMouseY(), (450 + (300/2)), 300 + 25, 40, 40))
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
      _gui.setTextureAt("./assets/sprites/rtype-logo.png", 380, 40, 1.);
      _gui.fillRec(0, 0, 1200, 800, 0x000000, 180);
      _gui.writeAt("loading" + displayDot, (1200/2) - 50, (800/2) - 50, 0x00ff00, 1.2);
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
  _gui.fillRec(0, 0, 1200, 800, 0x000000, 180);
  _gui.writeAt("Waiting Room", 300, 30, 0x00ff00, 1.2);
  _context = RTypeUI::Context::Game;
}

void                    RTypeUI::displayGame(void)
{
  static int            firstImageSpaceX = 0;
  static int            secondImageSpaceX = 1200;

  if (firstImageSpaceX == -1200)
    firstImageSpaceX = 0;
  if (secondImageSpaceX == 0)
    secondImageSpaceX = 1200;
  _gui.setTextureAt("./assets/sprites/rtype-space.jpg", firstImageSpaceX-=2, 0, 1.);
  _gui.setTextureAt("./assets/sprites/rtype-space.jpg", secondImageSpaceX-=2, 0, 1.);
}

void                    RTypeUI::displayMenu(void)
{
  _gui.setTextureAt("./assets/sprites/background.jpg", 0, 0, 1.);
  _gui.fillRec(0, 0, 1200, 800, 0x000000, 180);
}
