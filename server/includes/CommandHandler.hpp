#ifndef		__COMMANDHANDLER_HPP__
# define	__COMMANDHANDLER_HPP__

# include	<map>

# include	"Message.hpp"
# include	"Client.hpp"
# include	"RTypeServer.hpp"

# define	appelDeFonctionMembre(instance, ptr) ((instance).*(ptr))

class		RTypeServer;

class		CommandHandler
{

public:

  explicit	CommandHandler();
  ~CommandHandler();

  typedef bool	(CommandHandler::* f)(RTypeServer * server, Client & client, Message * message);

  bool		execFuncByOperationCode(RTypeServer * server, Client & client, Message * message);

  bool		logInUser(RTypeServer * server, Client & client, Message * message);
  bool		listOfRoom(RTypeServer * server, Client & client, Message * message);
  bool		createRoom(RTypeServer * server, Client & client, Message * message);
  bool		joinRoom(RTypeServer * server, Client & client, Message * message);

private:

  void			sendMessage(RTypeServer * server,
				    int opCode,
				    const std::string & ip,
				    int port,
				    void * data = NULL,
				    int size = 0);
  bool			checkId(const std::string & id);

  std::map< int, f >	_fptr;

};

#endif		// !__COMMANDHANDLER_HPP__
