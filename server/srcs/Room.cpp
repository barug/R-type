# include	<iostream>
# include	<sstream>
# include	"../includes/UnixSocket.hpp"
# include	"../includes/WinSocket.hpp"
# include       "../includes_ecs/serverMessages.hpp"
# include	"Room.hpp"

Room::Room(const std::string & name) :
  _name(name),
  _players(),
  _playersGameId(),
  _nbPlayers(0),
# ifdef		__unix__
  _socket(std::make_shared<UnixSocket>("0", 0)),
# elif		defined(_WIN32) || defined(WIN32)
  _socket(std::make_shared< WinSocket>("0", 0)),
# define	OS_Windows
# endif
  _commandHandler(std::make_shared< CommandHandlerGame>()),
  _gameEngine("./serverLibs/"),
  _locker(),
  _thread(std::thread(&Room::run, this)),
  _run(true)
{
}

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

bool		Room::addPlayer(const Client& clicli)
{
  _locker.try_lock();

  std::string	id = clicli.getIp() + ":" + std::to_string(clicli.getPort());
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

bool		Room::removePlayer(const Client& clicli)
{
  _locker.try_lock();

  std::string	id = clicli.getIp() + ":" + std::to_string(clicli.getPort());
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
  std::cout << "Engine !" << std::endl;
  _gameEngine.run();
  return false;
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
	  std::unique_ptr<Message>			message = std::make_unique<Message>(*data);
	  if (_playersGameId.size() < 2)
	    {
	      Message::Room				*room = (Message::Room *)message->getData();
	      _playersGameId.emplace(ipPort, room->_name);

	      std::size_t found = ipPort.find(':');

	      std::string ip = ipPort.substr(0, found);
	      std::cout << ip << std::endl;
	      
	      std::string tmpPort = ipPort.substr(found + 1);
	      std::stringstream ss;
	      int		port;

	      ss << tmpPort;
	      ss >> port;
	      _gameEngine.postImmediateMessage(ServerMessages::ADD_CLIENT, new std::pair<std::string, int>(data->_ip, data->_port));
	    }
	}
      if (_playersGameId.size() == 2)
	{
	  std::cout << _socket->getIp() << std::endl;
	  std::cout << _socket->getPort() << std::endl;
	  std::cout << "ImmediateMessageCall" << std::endl;
	  _gameEngine.postImmediateMessage(ServerMessages::SOCKET_ROOM, new std::pair<std::string, int>(_socket->getIp(), _socket->getPort()));
	  this->gameStep();
	}
    }
  return true;
}
