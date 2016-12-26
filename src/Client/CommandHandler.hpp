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

  bool			userLoggedIn(RTypeClient * client, Message * message);
  bool			listOfRoom(RTypeClient * client, Message * message);

private:

  std::map<int, f>	_fptr;

};

#endif		// !__COMMANDHANDLER_HPP__
