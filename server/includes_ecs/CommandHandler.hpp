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

  typedef bool		(CommandHandler::* f)(RTypeClient * client, Message * message);

  bool			execFuncByOperationCode(RTypeClient * client, Message * message);
  void			sendGameMessage(RTypeClient *client, int opCode, void * data = NULL, int size = 0);

  bool			userLoggedIn(RTypeClient * client, Message * message);
  bool			listOfRoom(RTypeClient * client, Message * message);
  bool			roomCreated(RTypeClient * client, Message * message);
  bool			roomJoined(RTypeClient * client, Message * message);

  bool			roomDontExist(RTypeClient * client, Message * message);
  bool			numberPlayerMax(RTypeClient * client, Message * message);
  bool			maxRoom(RTypeClient * client, Message * message);
  bool			illegaleId(RTypeClient * client, Message * message);
  bool			roomExist(RTypeClient * client, Message * message);

private:

  std::map<int, f>	_fptr;

};

#endif		// !__COMMANDHANDLER_HPP__
