#ifndef			__WINSOCKET_HPP__
# define		__WINSOCKET_HPP__

# include		<memory>

# ifdef		__unix__
# elif		defined(_WIN32) || defined(WIN32)

# include	<iostream>
# include	<winsock2.h>

# pragma	comment(lib,"ws2_32.lib") //Winsock Library
# endif

# include		"ISocket.hpp"

class			WinSocket : public ISocket
{

public :

  explicit						WinSocket(const std::string & ip, int port);
  virtual						~WinSocket();
  virtual const std::shared_ptr< ISocket::Datagram >	readSocket();
  virtual bool						writeSocket(const ISocket::Datagram & datagram);
  virtual const std::string&				getIp() const;
  virtual int						getPort() const;
  virtual int						getFd() const;
  virtual bool						addFdSelect(int fd);
  virtual int						somethingToRead();

private :

  virtual void		setFds();
  virtual int		checkFds();

  std::string		_ip;
  int			_port;
  int			_fd;
  struct timeval	_tv;
  fd_set		_readFd;
  int			_nbFds;
  int			_fdMax;

};

# endif			// !__SOCKETWIN_HPP__
