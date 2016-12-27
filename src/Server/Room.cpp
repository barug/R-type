# include	<iostream>

# include	"UnixSocket.hpp"
# include	"WinSocket.hpp"

# include	"Room.hpp"

Room::Room(const std::string & name) :
  _name(name),
  _players(),
  _nbPlayers(0),
# ifdef		__unix__
  _socket(std::make_shared<UnixSocket>("0", 0)),
# elif		defined(_WIN32) || defined(WIN32)
  _socket(std::make_shared< WinSocket>("0", 0)),
# define	OS_Windows
# endif
  _commandHandler(std::make_shared< CommandHandlerGame>()),
  _locker(),
  _thread(std::thread(&Room::run, this)),
  _run(true)
{}

Room::~Room()
{
  if (_thread.joinable())
    _thread.join();
}

const std::string  & Room::getName() const
{
  return _name;
}

int	Room::getNbPlayers() const
{
  return _nbPlayers;
}

const std::map< const std::string, std::shared_ptr< Client > > &	Room::getPlayers() const
{
  return _players;
}

std::shared_ptr< ISocket >	Room::getSocket() const
{
  return _socket;
}

bool	Room::addPlayer(const Client& clicli)
{
  _locker.try_lock();

  std::string id = clicli.getIp() + ":" + std::to_string(clicli.getPort());
  auto it = _players.find(id);
  if (_nbPlayers == 4 || it != _players.end())
    {
      _locker.unlock();
      return false;
    }

  _players.insert(std::pair<const std::string,
		  std::shared_ptr< Client > >(id, std::make_shared<Client>(clicli)));
  ++_nbPlayers;

  _locker.unlock();
  return true;
}

bool	Room::removePlayer(const Client& clicli)
{
  _locker.try_lock();

  std::string id = clicli.getIp() + ":" + std::to_string(clicli.getPort());
  auto it = _players.find(id);
  if (it == _players.end())
    {
      _locker.unlock();
      return false;
    }

  _players.erase(it);
  --_nbPlayers;

  _locker.unlock();
  return true;
}

const bool	Room::getRun() const
{
  bool		tmp = _run;

  return tmp;
}

void	Room::setRun(const bool state)
{
  _locker.lock();
  _run = state;
  _locker.unlock();
}

bool	Room::gameStep()
{
  // shall we do a new object ?
  std::cout << "And one more Step" << std::endl;
  return true;
}

bool	Room::run()
{
  bool	run = true;

  while (run)
    {
      _locker.lock();
      run = _run;
      _locker.unlock();

      if (_socket->somethingToRead() != -1)
	{

	  const std::shared_ptr<ISocket::Datagram>	data = _socket->readSocket();
	  std::string					ipPort(data->_ip + ":" + std::to_string(data->_port));
	  Client					clicli = *_players[ipPort];
	  std::unique_ptr<Message>			message = std::make_unique<Message>(*data);
	  std::cout << " [+] Game Cmd " << std::endl;
	  // _commandHandler->execFuncByOperationCode(this, *clicli, message.get());
	}
      if (_nbPlayers == 4)
	this->gameStep();
    }
  return true;
}
