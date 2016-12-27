#ifndef		__RTYPESERVER_HPP__
# define	__RTYPESERVER_HPP__

# include	"RoomManager.hpp"
# include	"NetworkHandler.hpp"
# include	"CommandHandler.hpp"

class		CommandHandler;

class		RTypeServer
{

public :

  explicit RTypeServer(const int port);
  ~RTypeServer();

  const NetworkHandler *		getNetworkHandler() const;
  const std::shared_ptr< RoomManager >	getRoomManager() const;

  void					run();

private :

  std::shared_ptr<NetworkHandler>	_networkHandler;
  std::shared_ptr<RoomManager>		_roomManager;
  std::unique_ptr< CommandHandler >	_commandHandler;
  bool					_run;
};

# endif		// !__RTYPESERVER_HPP__
