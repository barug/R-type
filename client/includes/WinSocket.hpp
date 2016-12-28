#ifndef			__WINSOCKET_HPP__
# define		__WINSOCKET_HPP__

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
  explicit                                              WinSocket();
  explicit						WinSocket(const std::string& ipServer, int portServer);
  virtual						~WinSocket();
  virtual void                                          connectToServer(const std::string &ipServer, int portServer);
  virtual const std::shared_ptr<ISocket::Datagram>	readSocket();
  virtual bool						writeSocket(const ISocket::Datagram& datagram);
  virtual const std::string&				getIpServer() const;
  virtual int						getPortServer() const;
  virtual const std::string&				getIp() const;
  virtual int						getPort() const;
  virtual int						getFd() const;
  virtual bool						somethingToRead();

private :

  virtual void				setFds();

  std::string				_ipServer;
  std::string				_ip;
  int						_portServer;
  int						_port;
  int						_fd;
  struct timeval			_tv;
  fd_set				_readFd;
};

# endif			// !__WINSOCKET_HPP__
