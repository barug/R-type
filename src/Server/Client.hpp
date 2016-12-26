#ifndef			__CLIENT_HPP__
# define		__CLIENT_HPP__

# include		<string>

# include		"ISocket.hpp"

class			Client
{

public :

  explicit		Client(const std::string& ip, int port);
  ~Client();

  bool			operator==(Client const& clicli);

  void			setIp(const std::string& ip);
  void			setPort(int port);

  const std::string&	getIp() const;
  int			getPort() const;

private :

  std::string		_ip;
  int			_port;

};

# endif			// !__CLIENT_HPP__
