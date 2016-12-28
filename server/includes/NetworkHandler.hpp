#ifndef		__NETWORKHANDLER_HPP_
# define	__NETWORKHANDLER_HPP_

# include	<memory>
# include	<string>
# include	<map>

# include	"Client.hpp"
# include	"ISocket.hpp"

class		NetworkHandler
{

public :

  explicit NetworkHandler(const int port);
  ~NetworkHandler();

  Client*							addClient(const std::string & key,
									  const std::string & ip,
									  int port);

  ISocket&							getSocket() const;
  const std::map< std::string, std::shared_ptr< Client > > &	getClient() const;
  Client*							getClientByKey(const std::string & key) const;

private :

  std::map< std::string, std::shared_ptr< Client > >		_client;
  std::unique_ptr< ISocket >					_socket;

};

# endif		// !__NETWORKHANDLER_HPP_
