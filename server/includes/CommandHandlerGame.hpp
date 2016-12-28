#ifndef		__COMMANDHANDLERGAME_HPP__
# define	__COMMANDHANDLERGAME_HPP__

# include	<map>

# include	"Message.hpp"
# include	"Client.hpp"
# include	"Room.hpp"

# define	appelDeFonctionMembre(instance, ptr) ((instance).*(ptr))

class		Room;

class		CommandHandlerGame
{

public :

  explicit CommandHandlerGame();
  ~CommandHandlerGame();

  typedef bool		(CommandHandlerGame::* f)(Room *room, Client &client, Message *message);

  bool			execFuncByOperationCode(Room *room, Client &client, Message *message);

private:

  std::map<int, f>	_fptr;

};

# endif // !__COMMANDHANDLERGAME_HPP__
