//
// rtype
//

# include       "Core.hpp"
# include       "Window.hpp"

Core::Core(int ac, char **av)
  : _gui(new Window("RType", 800, 600, "./assets/font/digital.otf")),
    _client(new RTypeClient()),
    _rtypeUI(*_gui),
    _ip(),
    _port(0),
    _contextHandler({{RTypeUI::Context::Introduction,            &Core::_handleIntroduction},
		     {RTypeUI::Context::Authentification,        &Core::_handleAuthentification},
		     {RTypeUI::Context::WaitingRoom,             &Core::_handleWaitingRoom},
		     {RTypeUI::Context::Game,                    &Core::_handleGame},
		     {RTypeUI::Context::Loading,                 &Core::_handleLoading}}),
    _gameEngine("./ECS/mods/")
{
  if (ac == 3)
    {
      if (!_checkArgs(ac, av))
	{
	  std::cerr << "Usage:\n\t./" << av[0] << " ip_server port_server" << std::endl;
	  std::exit(1);
	}
      else
	{
	  _ip = std::string(av[1]);
	  _port = std::atoi(av[2]);
	  _client->connectToServer(_ip, _port);
	  _rtypeUI.setContext(RTypeUI::Context::WaitingRoom);
	}
    }
}

Core::~Core()
{}

void            Core::gameLoop()
{
  while (_gui->isAlive())
    {
      _client->run();
      _gui->clear();
      _gui->handleEvents();
      ((*this).*(_contextHandler[_rtypeUI.getContext()]))();
      _gui->display();
    }
}

void            Core::_handleIntroduction(void)
{
  _rtypeUI.displayIntroduction();
}

void            Core::_handleLoading(void)
{
  _rtypeUI.displayLoading();
}


void            Core::_handleAuthentification(void)
{
  _rtypeUI.displayAuthentification(&_ip, &_port);
  if (!_ip.empty() && _rtypeUI.getContext() != RTypeUI::Context::Authentification)
    {
      _client->connectToServer(_ip, _port);
      std::cout << "ip == > " << _ip << " et " << _port << std::endl;
    }
}

void            Core::_handleWaitingRoom(void)
{
  _rtypeUI.displayWaitingRoom();
}

void            Core::_handleGame(void)
{
  _gameEngine.run();
}

bool		Core::_checkArgs(int ac, char **av)
{
  int           i;
  int           d;
  int           dd;

  for (i = 0; av[2][i]; i++)
    if (av[2][i] < '0' || av[2][i] > '9')
      return false;
  for (i = 0, d = 0, dd = 0; av[1][i]; i++)
    if ((av[1][i] < '0' || av[1][i] > '9' )  &&
	((av[1][i] == '.' && (dd || ++d == 4)) ||
	 (av[1][i] == ':' && (d || ++dd == 8))))
      return false;
  return (dd == 7 || d == 3 || (av[1][0] == '0' && av[1][1] == 0)) ? true : false;
}
