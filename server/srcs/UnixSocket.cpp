# ifdef		__unix__

# include	<iostream>
# include	<unistd.h>
# include	<arpa/inet.h>
# include	<string.h>

# include	"UnixSocket.hpp"

UnixSocket::UnixSocket(const std::string& ip, int port) :
  _ip(ip),
  _port(port),
  _fd(),
  _tv({1, 0}),
  _readFd(),
  _fds(),
  _nbFds(0)
{
  struct sockaddr_in	s_in = { 0, 0, 0, 0, 0, 0, 0, 0 };
  socklen_t		addressLength = sizeof(s_in);

  s_in.sin_family = AF_INET;
  s_in.sin_addr.s_addr = inet_addr(_ip.c_str());
  s_in.sin_port = htons(_port);

  if ( (_fd = socket(s_in.sin_family, SOCK_DGRAM, 0)) == -1 )
    throw std::string("Error ! Cannot creat the socket.");
  else if (bind(_fd, (struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    {
      close(_fd);
      throw std::string("Error ! Cannot bind the socket.");
    }

  getsockname(_fd, (struct sockaddr*)&s_in, &addressLength);

  _fds[_nbFds++] =_fd;
  _ip = inet_ntoa(s_in.sin_addr); //review ip
  _port = ntohs(s_in.sin_port);
}

UnixSocket::~UnixSocket()
{
  // use a expect catch ?
  close(_fd);
}

const std::shared_ptr<ISocket::Datagram>	UnixSocket::readSocket()
{
  std::shared_ptr<ISocket::Datagram>		datagram = std::make_shared<ISocket::Datagram>();
  struct sockaddr_in				s_addr =  { 0, 0, 0, 0 };
  socklen_t					s_len = sizeof(s_addr);

  bzero(datagram->_data, BUFFLEN);
  if ((datagram->_lenght = recvfrom(_fd,  datagram->_data,  sizeof datagram->_data - 1 ,
				    0, (struct sockaddr *)&s_addr, &s_len)) < 0)
    return datagram;

  // DEBUG
  std::cout << " [+] Received packet from " << inet_ntoa(s_addr.sin_addr)
	    << ":" <<  ntohs(s_addr.sin_port) << std::endl;

  datagram->_ip = inet_ntoa(s_addr.sin_addr);
  datagram->_port = ntohs(s_addr.sin_port);
  return datagram;
}

bool			UnixSocket::writeSocket(const ISocket::Datagram& datagram)
{
  struct sockaddr_in	s_addr =  { 0, 0, 0, 0, 0, 0, 0, 0 };
  socklen_t		s_len;

  s_addr.sin_family = AF_INET;
  s_addr.sin_addr.s_addr = inet_addr(datagram._ip.c_str());
  s_addr.sin_port = htons(datagram._port);
  s_len = sizeof(s_addr);

  if (sendto(_fd, datagram._data, datagram._lenght,
	     0, (struct sockaddr *)&s_addr, s_len) == -1)
    return false;

  std::cout << " [+] Write packet to " << inet_ntoa(s_addr.sin_addr)
	    << ":" <<  ntohs(s_addr.sin_port) << std::endl;

  return true;
}

const std::string&	UnixSocket::getIp() const
{
  return _ip;
}

int	UnixSocket::getPort() const
{
  return _port;
}

int	UnixSocket::getFd() const
{
  return _fd;
}

bool	UnixSocket::addFdSelect(int fd)
{
  if (_nbFds == 2)
    return false;
  _fds[_nbFds++] = fd;
  return true;
}

void	UnixSocket::setFds()
{
  FD_ZERO(&_readFd);
  for (int i = 0, _fdMax = 0; i < _nbFds; i++)
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
