# include	<iostream>
# include	<sstream>

# include	<string.h>
# include	<cstring>

# include	"../includes/CommandHandler.hpp"

CommandHandler::CommandHandler() :
  _fptr{ {101, &CommandHandler::logInUser },
	 {102, &CommandHandler::listOfRoom },
	 {103, &CommandHandler::createRoom },
	 {104, &CommandHandler::joinRoom } }
{}

CommandHandler::~CommandHandler()
{}

bool	CommandHandler::execFuncByOperationCode(RTypeServer *server,
						Client& client,
						Message* message)
{
  auto it = _fptr.find((int)message->getOperationCode());
  if (it == _fptr.end())
    return false;
  return appelDeFonctionMembre(*this, it->second)(server, client, message);
}

void				CommandHandler::sendMessage(RTypeServer * server,
							    int opCode,
							    const std::string & ip,
							    int port,
							    void * data,
							    int size)
{
  std::cout << " \033[1;33m[+] Reaction" << ((opCode < 100) ? " 00" : " ");
  std::cout << opCode;
  std::cout << " is invoque\033[0m" << std::endl;

  std::shared_ptr< Message >	message = std::make_shared< Message >(opCode, ip, port, data, size);
  server->getNetworkHandler()->getSocket().writeSocket(*(message->createDatagram()));
}

bool		CommandHandler::logInUser(RTypeServer *server,
					  Client &client,
					  Message *message)
{
  std::cout << " \033[1;32m[+] Action 101 is managed\033[0m" << std::endl;

  this->sendMessage(server, 1, client.getIp(), client.getPort());

  std::string	str = server->getRoomManager()->getFirstIdForRoom();
  
  if (!str.empty())
    {
      std::shared_ptr<Message> pM = std::make_shared<Message>(104, client.getIp(), client.getPort(), (char*) str.c_str(), str.size()); 
      this->joinRoom(server, client, pM.get());
      return true;
    }
}

bool						CommandHandler::listOfRoom(RTypeServer *server,
									   Client &client,
									   Message *message)

{
  std::cout << " \033[1;32m[+] Action 102 is managed\033[0m" << std::endl;

  Message::ListOfRoom				answer = {};
  std::vector<Message::Room>			rooms;
  std::vector<Message::Entity>			players;
  std::stringstream				ss;
  
  answer._nbRoom = server->getRoomManager()->getRoomNumber();
  std::cout << "Nbr of Rooms" << answer._nbRoom << std::endl;
  for (auto it : server->getRoomManager()->getGameRooms())
    {
      int				        i = -1;
      Message::Room				currentRoom = {};

      for (auto name : it.second->getName())
	currentRoom._name[++i] = name;
      
      currentRoom._port = it.second->getSocket()->getPort();

      i = -1;
      for (auto ip : it.second->getSocket()->getIp())
	currentRoom._ip[++i] = ip;

      currentRoom._nbPlayer = it.second->getNbPlayers();

      
      for (auto currentPlayer : it.second->getPlayers())
	{
	  i = -1;
	  Message::Entity		player = {};

	  for (auto car : currentPlayer.second->getIp())
	    player._name[++i] = car;
	  player._name[++i] = ':';
	  for (auto car : std::to_string(currentPlayer.second->getPort()))
	    player._name[++i] = car;
	  i = -1;
	  players.push_back(player);
	}
      rooms.push_back(currentRoom);      
    }
  
  ss.write((char*) &answer, sizeof(answer));
  int	countPlayer = 0;
  int	nbPlayerWrite = 0;
  for (auto room : rooms)
    {
      ss.write((char*) &room, sizeof(room));
      countPlayer += room._nbPlayer;
      for (;nbPlayerWrite < countPlayer; ++nbPlayerWrite)
	ss.write((char *) &(players[nbPlayerWrite]), sizeof(players[nbPlayerWrite]));
    }
  this->sendMessage(server, 2, client.getIp(), client.getPort(),
		    (void *)ss.str().c_str(), ss.str().size());
  return true;
}

  bool	CommandHandler::checkId(const std::string & id)
  {
    for (auto it : id)
      if ( !(it >= 'a' && it <= 'z') &&
	   !(it >= 'A' && it <= 'Z') &&
	   !(it >= '0' && it <= '9') )
	return false;
    return true;
  }

  bool		CommandHandler::createRoom(RTypeServer *server,
					   Client &client,
					   Message *message)
  {
    std::cout << " \033[1;32m[+] Action 103 is managed\033[0m" << std::endl;

    char	*	id;
    memcpy(&id, (char *)message->getData(), message->getSize());

    std::string	str(id);
    std::cout << id << std::endl;

    if (!this->checkId(str))
      this->sendMessage(server, 204, client.getIp(), client.getPort());
    else if (!server->getRoomManager()->getRoomById(id))
      {
	if (server->getRoomManager()->getRoomNumber() == MAX_ROOM)
	  this->sendMessage(server, 203, client.getIp(), client.getPort());
	server->getRoomManager()->createRoom(str);
	this->sendMessage(server, 3, client.getIp(), client.getPort());
	this->joinRoom(server, client, message);
      }
    else
      this->sendMessage(server, 205, client.getIp(), client.getPort());

    return false;
  }

  bool							CommandHandler::joinRoom(RTypeServer *server,
										 Client &client,
										 Message *message)
  {
    std::cout << " \033[1;32m[+] Action 104 is managed\033[0m" << std::endl;

    char *						id = (char *)message->getData();

    std::string						str(id);
    Room *						room = server->getRoomManager()->getRoomById(str);

    if (room)
      {
	if (room->getNbPlayers() < 4)
	  {
	    room->addPlayer(client);
	  
	    int						i = -1;
	    std::stringstream				ss;
	    Message::Room				answer = {};
	    std::vector<Message::Entity>			players;

	    for (auto name : room->getName())
	      answer._name[++i] = name;
      
	    answer._port = room->getSocket()->getPort();

	    i = -1;
	    for (auto ip : room->getSocket()->getIp())
	      answer._ip[++i] = ip;

	    answer._nbPlayer = room->getNbPlayers();

	    for (auto currentPlayer : room->getPlayers())
	      {
		i = -1;
		Message::Entity		player = {};

		for (auto car : currentPlayer.second->getIp())
		  player._name[++i] = car;
		player._name[++i] = ':';
		for (auto car : std::to_string(currentPlayer.second->getPort()))
		  player._name[++i] = car;
		i = -1;
		players.push_back(player);
	      }
	    ss.write((char *) &answer, sizeof(answer));

	    for (auto it : players)
	      ss.write((char *) &it, sizeof(it));

	    this->sendMessage(server, 4, client.getIp(), client.getPort(),
			      (void *)ss.str().c_str(), ss.str().size());
	    return true;
	  }
	else
	  this->sendMessage(server, 202, client.getIp(), client.getPort());
      }
    else
      this->sendMessage(server, 201, client.getIp(), client.getPort());
    return false;
  }
