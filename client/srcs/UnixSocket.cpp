// # ifdef __unix__
# include	<iostream>
# include	<unistd.h>
# include	<arpa/inet.h>
# include	<string.h>

# include	"UnixSocket.hpp"

UnixSocket::UnixSocket() :
  _ipServer(),
  _ip(),
  _portServer(),
  _port(),
  _fd(),
  _tv(),
  _readFd()
{}

UnixSocket::UnixSocket(const std::string& ipServer, int portServer) :
  _ipServer(ipServer),
  _ip(),
  _portServer(portServer),
  _port(),
  _fd(),
  _tv(),
  _readFd()
{
  if ( (_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
    {
      // cannot bind socket; throw ?
    }
  _tv.tv_usec = 500;
  _tv.tv_sec = 0;
}

UnixSocket::~UnixSocket()
{
  // use a expect catch ?
  if (_fd >= 0)
    close(_fd);
}
void                                            UnixSocket::connectToServer(const std::string &ipServer, int portServer)
{
  _ipServer = ipServer;
  _portServer = portServer;
  if ( (_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
    {
      // cannot bind socket; throw ?
    }
  _tv.tv_usec = 500;
  _tv.tv_sec = 0;
}

const std::shared_ptr<ISocket::Datagram>	UnixSocket::readSocket()
{
  std::shared_ptr<ISocket::Datagram>		datagram = std::make_shared<ISocket::Datagram>();
  struct sockaddr_in				s_addr =  { 0, 0, 0, 0 };
  socklen_t					s_len = sizeof s_addr;

  bzero(datagram->_data, BUFFLEN);
  if ((datagram->_lenght = recvfrom(_fd,  datagram->_data,  sizeof datagram->_data - 1 ,
				    0, (struct sockaddr *)&s_addr, &s_len)) < 0)
    return datagram;

  // DEBUG
  std::cout << " [+] Received packet from " << inet_ntoa(s_addr.sin_addr)
	    << ":" <<  ntohs(s_addr.sin_port)
	    << "(" << datagram->_lenght << ")" << std::endl;

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
  return true;
}

const std::string&	UnixSocket::getIpServer() const
{
  return _ipServer;
}

int	UnixSocket::getPortServer() const
{
  return _portServer;
}

const std::string&	UnixSocket::getIp() const
{
  return _ip;
}

int	UnixSocket::getPort() const
{
  return _port;
}

int UnixSocket::getFd() const
{
  return _fd;
}

void	UnixSocket::setFds()
{
  FD_ZERO(&_readFd);
  FD_SET(_fd, &_readFd);
  if (!_tv.tv_usec)
    _tv.tv_usec = 500;
}

bool	UnixSocket::somethingToRead()
{
  this->setFds();
  if (select(_fd + 1, &_readFd,
	     NULL, NULL, &_tv) == -1 )
    { /* maybe some clean of code there */ }
  return (FD_ISSET(_fd, &_readFd)) ? true : false;
}
// # endif
