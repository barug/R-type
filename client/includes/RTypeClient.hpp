#ifndef			__RTYPECLIENT_HPP__
# define		__RTYPECLIENT_HPP__

# include		<string>

# include		"CommandHandler.hpp"
# include		"NetworkHandler.hpp"

class			CommandHandler;

class			RTypeClient
{

public :

  explicit RTypeClient();
  explicit RTypeClient(const std::string ip, const int port);
  ~RTypeClient();

  const NetworkHandler *		getNetworkHandler() const;
  void					connectToServer(const std::string &ip, const int port);
  void					run();

private :
  std::shared_ptr<NetworkHandler>	_networkHandler;
  std::unique_ptr<CommandHandler>	_commandHandler;

};

# endif			// !__RTYPECLIENT_HPP__
