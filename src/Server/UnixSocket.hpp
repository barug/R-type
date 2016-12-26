# ifdef		__unix__
#ifndef			__UNIXSOCKET_HPP__
# define		__UNIXSOCKET_HPP__

# include		<memory>

# include		"ISocket.hpp"

class			UnixSocket : public ISocket
{

public :

  explicit						UnixSocket(const std::string & ip, int port);
  virtual						~UnixSocket();
  virtual const std::shared_ptr< ISocket::Datagram >	readSocket();
  virtual bool						writeSocket(const ISocket::Datagram & datagram);
  virtual const std::string&				getIp() const;
  virtual int						getPort() const;
  virtual int						getFd() const;
  virtual bool						somethingToRead();

private :

  virtual void		setFds();

  std::string		_ip;
  int			_port;
  int			_fd;
  struct timeval	_tv;
  fd_set		_readFd;

};

# endif			// !__UNIXSOCKET_HPP__
# endif
