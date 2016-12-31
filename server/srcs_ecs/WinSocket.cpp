# if            defined(__unix__)
# elif		defined(_WIN32) || defined(WIN32)
# include	<winsock2.h>
# pragma	comment(lib,"ws2_32.lib") //Winsock Library

# include	<iostream>
# include	<string.h>

# include	"../includes/WinSocket.hpp"

WinSocket::WinSocket() :
  _ipServer(),
  _ip(),
  _portServer(),
  _port(),
  _fd(),
  _tv(),
  _readFd()
{
}

WinSocket::WinSocket(const std::string& ipServer, int portServer) :
_ipServer(ipServer),
_ip(),
_portServer(portServer),
_port(),
_fd(),
_tv(),
_readFd()
{
  WSADATA		wsa;

  if (WSAStartup(MAKEWORD(2,2),&wsa) < 0)
    {
      /* cannot Initialise winsock; throw ? */
    }
  else if((_fd = socket(AF_INET, SOCK_DGRAM , 0 )) == INVALID_SOCKET )
    {
      WSACleanup();
      // cannot creqte socket; throw ?
    }
  _tv.tv_usec = 500;
  _tv.tv_sec = 0;
}

WinSocket::~WinSocket()
{
  // use a expect catch ?
  if (_fd != SOCKET_ERROR)
    closesocket(_fd);
  WSACleanup();
}

void                                            WinSocket::connectToServer(const std::string &ipServer, int portServer)
{
  WSADATA		wsa;

  _ipServer = ipServer;
  _portServer = portServer;
  if (WSAStartup(MAKEWORD(2,2),&wsa) < 0)
    {
      /* cannot Initialise winsock; throw ? */
    }
  else if((_fd = socket(AF_INET, SOCK_DGRAM , 0 )) == INVALID_SOCKET )
    {
      WSACleanup();
      // cannot creqte socket; throw ?
    }
  _tv.tv_usec = 500;
  _tv.tv_sec = 0;

}

const std::shared_ptr<ISocket::Datagram>	WinSocket::readSocket()
{
  std::shared_ptr<ISocket::Datagram>		datagram = std::make_shared<ISocket::Datagram>();
  SOCKADDR_IN					S_addr =  { 0, 0, 0, 0 };
  int						s_len = sizeof S_addr;

  memset(datagram->_data, 0, BUFFLEN);
  if ((datagram->_lenght = recvfrom(_fd,  datagram->_data,  sizeof datagram->_data - 1,
				    0, (SOCKADDR *)&S_addr, &s_len)) < 0)
    return datagram;
  datagram->_data[datagram->_lenght] = 0;

  std::cout << " [+] Received packet from " << inet_ntoa(S_addr.sin_addr)
	    << ":" <<  ntohs(S_addr.sin_port);

  datagram->_ip = inet_ntoa(S_addr.sin_addr);
  datagram->_port = ntohs(S_addr.sin_port);
  return datagram;
}

bool			WinSocket::writeSocket(const ISocket::Datagram& datagram)
{
	struct sockaddr_in		S_addr;// = { 0, 0, 0, 0, 0, 0, 0, 0 };
  int			s_len;

  S_addr.sin_addr.s_addr = inet_addr(_ipServer.c_str());
  S_addr.sin_port = htons(_portServer);
  S_addr.sin_family = AF_INET;
  s_len = sizeof(S_addr);

  if (sendto(_fd, datagram._data, datagram._lenght,
	     0, (SOCKADDR *)&S_addr, s_len) < 0)
    return false;
  return true;
}

const std::string&	WinSocket::getIpServer() const
{
  return _ipServer;
}

int	WinSocket::getPortServer() const
{
  return _portServer;
}

const std::string&	WinSocket::getIp() const
{
  return _ip;
}

int	WinSocket::getPort() const
{
  return _port;
}

int     WinSocket::getFd() const
{
  return _fd;
}

void	WinSocket::setFds()
{
  FD_ZERO(&_readFd);
  FD_SET(_fd, &_readFd);
  if (!_tv.tv_usec)
    _tv.tv_usec = 500;
}

bool	WinSocket::somethingToRead()
{
  this->setFds();
  if (select(_fd + 1, &_readFd,
	     NULL, NULL, &_tv) == -1 )
    { /* maybe some clean of code there */ }
  return (FD_ISSET(_fd, &_readFd)) ? true : false;
}

# endif
