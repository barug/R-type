# include	<iterator>
# include	<iostream>
# include	"../includes_ecs/NetworkHandler.hpp"
# include	"../includes_ecs/UnixSocket.hpp"
# include	"../includes_ecs/WinSocket.hpp"

NetworkHandler::NetworkHandler(const std::string &ip, const int port) :
# if defined (__unix__)
  _socket(new UnixSocket(ip, port)),
# elif		defined(_WIN32) || defined(WIN32)
  _socket(new WinSocket(ip, port)),
# define	OS_Windows
# endif
  _socketGame()
{
}

NetworkHandler::NetworkHandler() :
# if defined (__unix__)
  _socket(new UnixSocket)
# elif		defined(_WIN32) || defined(WIN32)
  _socket(new WinSocket)
# define	OS_Windows
# endif
{
}

NetworkHandler::~NetworkHandler()
{}

void        NetworkHandler::connectToServer(const std::string &ip, const int port)
{
   _socket->connectToServer(ip, port);
}

ISocket&	NetworkHandler::getSocket() const
{
  return *(_socket).get();
}

ISocket&	NetworkHandler::getSocketGame() const
{
  return *(_socketGame).get();
}

void	        NetworkHandler::setSocketGame(const int port)
{
# if defined (__unix__)
  _socketGame = std::make_unique<UnixSocket>(_socket->getIpServer(), port);
# elif		defined(_WIN32) || defined(WIN32)
  _socketGame = std::make_unique<WinSocket>(_socket->getIpServer(), port);
# define	OS_Windows
# endif
}
