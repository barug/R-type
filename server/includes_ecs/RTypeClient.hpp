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

  NetworkHandler *			getNetworkHandler() const;
  void					setNetworkHandler(std::shared_ptr<NetworkHandler> &ptr);
  bool					connectToServer(const std::string &ip, const int port);
  bool					run();

private :
  std::shared_ptr<NetworkHandler>	_networkHandler;
  std::unique_ptr<CommandHandler>	_commandHandler;
  bool					_askedForAuth;
  bool					_isAuthentified;
};

# endif			// !__RTYPECLIENT_HPP__
