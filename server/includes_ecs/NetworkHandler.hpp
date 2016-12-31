#ifndef			__NETWORKHANDLER_HPP_
# define		__NETWORKHANDLER_HPP_

# include		<memory>
# include		<string>
# include		<map>

# include		"ISocket.hpp"

class			NetworkHandler
{

public :
  
  explicit NetworkHandler();
  explicit NetworkHandler(const std::string &ip, const int port);
  ~NetworkHandler();

  void                          connectToServer(const std::string &ip, const int port);
  ISocket&			getSocket() const;
  ISocket&			getSocketGame() const;

  void				setSocketGame(const int port);
  
private :

  std::unique_ptr< ISocket >	_socket;
  std::unique_ptr< ISocket >	_socketGame;
};

# endif			// !__NETWORKHANDLER_HPP_
