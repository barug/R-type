# if		defined(_WIN32) || defined(WIN32)

# include	<iostream>
# include	<winsock2.h>

# pragma	comment(lib,"ws2_32.lib") //Winsock Library

# include	"WinSocket.hpp"

WinSocket::WinSocket(const std::string& ip, int port) :
  _ip(ip),
  _port(port),
  _fd(),
  _tv({1, 0}),
  _readFd(),
  _fds(),
  _nbFds(0)
{
  SOCKADDR_IN		s_in = { 0, 0, 0, 0, 0, 0, 0, 0 };
  SOCKLEN_T_t		addressLength = sizeof(s_in);
  WSADATA		wsa;

  s_in.sin_family = AF_INET;
  s_in.sin_addr.s_addr = inet_addr(_ip.c_str());
  s_in.sin_port = htons(_port);

  if (WSAStartup(MAKEWORD(2,2),&wsa) < 0)
    throw std::string("Error ! Cannot creat the socket.");
  else if((_fd = socket(s_in.sin_family, SOCK_DGRAM , 0 )) == INVALID_SOCKET ||
	  (bind(_fd, (struct sockaddr*)&s_in, sizeof(s_in)) == SOCKET_ERROR) )
    {
      if (_fd != -1)
	{
	  closesocket(_fd);
	  WSACleanup();
	  throw std::string("Error ! Cannot bind the socket.");
	}
      WSACleanup();
      throw std::string("Error ! Cannot create the socket.");
    }

  getsockname(_fd, (SOCKADDR *)&s_in, &addressLength);

  _fds[_nbFds++] =_fd;
  _ip = inet_ntoa(s_in.sin_addr);
  _port = ntohs(s_in.sin_port);
}

WinSocket::~WinSocket()
{
  // use a expect catch ?
  if (_fd != SOCKET_ERROR)
    closesocket(_fd);
  WSACleanup();
}

const std::shared_ptr<ISocket::Datagram>	WinSocket::readSocket()
{
  std::shared_ptr<ISocket::Datagram>		datagram = std::make_shared<ISocket::Datagram>();
  struct sockaddr_in S_addr = { 0, 0, 0, 0 };
  int				s_len;

  s_len = sizeof(S_addr);
  if ((datagram->_lenght = recvfrom(_fd,  datagram->_data,  sizeof datagram->_data - 1,
				    0, (struct sockaddr *)&S_addr, &s_len)) == -1)
    return datagram;
  datagram->_data[datagram->_lenght] = 0;

  // debug
  std::cout << "Received packet from " << inet_ntoa(S_addr.sin_addr)
	    << ":" <<  ntohs(S_addr.sin_port) << "\nData :"
	    << datagram->_data << " of size " << datagram->_lenght << std::endl;

  datagram->_ip = inet_ntoa(S_addr.sin_addr);
  datagram->_port = ntohs(S_addr.sin_port);
  return datagram;
}

bool		WinSocket::writeSocket(const ISocket::Datagram& datagram)
{
  SOCKADDR_IN	S_addr =  { 0, 0, 0, 0, 0, 0, 0, 0 };
  int		s_len;

  S_addr.sin_family = AF_INET;
  S_addr.sin_addr.s_addr = inet_addr(_ip.c_str());
  S_addr.sin_port = htons(_port);
  s_len = sizeof(S_addr);
  if (sendto(_fd, datagram._data, datagram._lenght,
	     0, (SOCKADDR *)&S_addr, s_len) == -1)
    return false;
  return true;
}

const std::string&	WinSocket::getIp() const
{
  return _ip;
}

int	WinSocket::getPort() const
{
  return _port;
}

int WinSocket::getFd() const
{
  return _fd;
}


bool	UnixSocket::addFdSelect(int fd)
{
  if (_nbFds >= 2)
    return false;
  _fds[_nbFds++] = fd;
  return true;
}

void	UnixSocket::setFds()
{
  FD_ZERO(&_readFd);
  _fdMax = 0;
  for (int i = 0; i < _nbFds; i++)
    {
      if (_fds[i] > _fdMax)
	_fdMax = _fds[i];
      FD_SET(_fds[i], &_readFd);
    }
  if (!_tv.tv_usec)
    _tv.tv_usec = 500;
  _fdMax++;
}

int	UnixSocket::checkFds()
{
  for (int i = 0; i < _nbFds; i++)
    if (FD_ISSET(_fds[i], &_readFd))
      return _fds[i];
  return -1;
}

int	UnixSocket::somethingToRead()
{
  this->setFds();
  if (select(_fdMax, &_readFd,
	     NULL, NULL, &_tv) == -1 )
    { /* maybe some clean of code there */ }
  return this->checkFds();
}

# endif
