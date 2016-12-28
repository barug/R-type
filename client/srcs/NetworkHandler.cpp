# include	<iterator>

# include	"NetworkHandler.hpp"
# include	"UnixSocket.hpp"
# include	"WinSocket.hpp"

NetworkHandler::NetworkHandler(const std::string ip, const int port) :
# if defined (__unix__)
  _socket(new UnixSocket(ip, port))
# elif		defined(_WIN32) || defined(WIN32)
  _socket(new WinSocket(ip, port))
# define	OS_Windows
# endif
{}

NetworkHandler::NetworkHandler() :
# if defined (__unix__)
  _socket(new UnixSocket)
# elif		defined(_WIN32) || defined(WIN32)
  _socket(new WinSocket)
# define	OS_Windows
# endif
{}

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