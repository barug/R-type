#ifndef		__COMMANDHANDLER_HPP__
# define	__COMMANDHANDLER_HPP__

# include	<map>

# include	"Message.hpp"
# include	"RTypeClient.hpp"

# define	appelDeFonctionMembre(instance, ptr) ((instance).*(ptr))

class		RTypeClient;

class		CommandHandler
{

public:

  explicit CommandHandler();
  ~CommandHandler();

  typedef bool		(CommandHandler::* f)(RTypeClient * client, Message * message, int sock);

  bool			execFuncByOperationCode(RTypeClient * client, Message * message, int sock);

  void			sendGameMessage(RTypeClient *client, int opCode, void * data = NULL, int size = 0);
  void			sendMessage(RTypeClient *client, int opCode, void * data = NULL, int size = 0);

  bool			userLoggedIn(RTypeClient * client, Message * message, int sock);
  bool			listOfRoom(RTypeClient * client, Message * message, int sock);
  bool			roomCreated(RTypeClient * client, Message * message, int sock);
  bool			roomJoined(RTypeClient * client, Message * message, int sock);
  bool			gameStarted(RTypeClient * client, Message * message, int sock);

  bool			roomDontExist(RTypeClient * client, Message * message, int sock);
  bool			numberPlayerMax(RTypeClient * client, Message * message, int sock);
  bool			maxRoom(RTypeClient * client, Message * message, int sock);
  bool			illegaleId(RTypeClient * client, Message * message, int sock);
  bool			roomExist(RTypeClient * client, Message * message, int sock);

private:

  std::map<int, f>	_fptr;

};

#endif		// !__COMMANDHANDLER_HPP__
