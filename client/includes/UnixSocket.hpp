# ifdef __unix__
#ifndef			__UNIXSOCKET_HPP__
# define		__UNIXSOCKET_HPP__

# include		"ISocket.hpp"

class			UnixSocket : public ISocket
{

public :
  explicit                                              UnixSocket();
  explicit						UnixSocket(const std::string& ipServer, int portServer);
  virtual						~UnixSocket();

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
  int					_portServer;
  int					_port;
  int					_fd;
  struct timeval			_tv;
  fd_set				_readFd;

};

# endif			// !__UNIXSOCKET_HPP__
# endif
