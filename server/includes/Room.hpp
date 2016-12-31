#ifndef		__ROOM_HPP__
# define	__ROOM_HPP__

# include	<map>
# include	<memory>

# include	<thread>
# include	<mutex>

# include	"ISocket.hpp"
# include	"GameEngine.hpp"
# include	"CommandHandlerGame.hpp"

class		CommandHandlerGame;

class		Room
{

public :

  explicit					Room(const std::string & name);
  ~Room();

  const std::string &				getName() const;
  int						getNbPlayers() const;
  const std::map< const std::string,
		  std::shared_ptr< Client > > &	getPlayers() const;
  std::shared_ptr< ISocket >			getSocket() const;

  bool						addPlayer(const Client & clicli);
  bool						removePlayer(const Client & clicli);

  const bool					getRun() const;
  void						setRun(const bool state);

  bool						run();

private :

  bool						gameStep();

  std::string					_name;
  std::map< const std::string,
	    std::shared_ptr< Client > >		_players;
  std::map< const std::string,
	    const std::string>			_playersGameId;
  int						_nbPlayers;

  std::shared_ptr< ISocket >			_socket;
  std::shared_ptr< CommandHandlerGame >		_commandHandler;

  GameEngine					_gameEngine;
  std::mutex					_locker;
  std::thread					_thread;

  bool						_run;

  // ESC
};

# endif		// !__ROOM_HPP__
