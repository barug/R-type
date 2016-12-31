#ifndef			__ISOCKET_HPP__
# define		__ISOCKET_HPP__

# include		<string>
# include		<memory>

# define		BUFFLEN (8192)

class			ISocket
{

public :

  struct		Datagram
  {
    char		_data[BUFFLEN];
    size_t		_lenght;
    std::string		_ip;
    int			_port;
  };

public :

  virtual						~ISocket() {};
  virtual void                                          connectToServer(const std::string &ipServer, int portServer) = 0;
  virtual const std::shared_ptr<ISocket::Datagram>	readSocket() = 0;
  virtual bool						writeSocket(const ISocket::Datagram &datagram) = 0;
  virtual const std::string&				getIpServer() const = 0;
  virtual int						getPortServer() const = 0;
  virtual const std::string&				getIp() const = 0;
  virtual int						getPort() const = 0;
  virtual int						getFd() const = 0;
  virtual bool						somethingToRead() = 0;

private :

  virtual void		setFds() = 0;

};

# endif			// !__ISOCKET_HPP__

// http://broux.developpez.com/articles/c/sockets/#L2-1-2-d
// http://www.binarytides.com/udp-socket-programming-in-winsock/
