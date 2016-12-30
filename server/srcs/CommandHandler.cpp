# include	<iostream>
# include	<sstream>

# include	<string.h>
# include	<cstring>

# include	"CommandHandler.hpp"

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
  this->listOfRoom(server, client, message);

  return true;
}

bool						CommandHandler::listOfRoom(RTypeServer *server,
									   Client &client,
									   Message *message)

{
  std::cout << " \033[1;32m[+] Action 102 is managed\033[0m" << std::endl;

  std::shared_ptr<Message::ListOfRoom>		listOfRoom = std::make_shared<Message::ListOfRoom>();
  //Message::Room					roomVector[MAX_ROOM];
  int						j = -1;
  std::stringstream				ss;

  listOfRoom->_nbRoom = server->getRoomManager()->getRoomNumber();
  std::cout << "Nbr of Rooms" << listOfRoom->_nbRoom << std::endl;
  for (auto it : server->getRoomManager()->getGameRooms())
    {
      int					i = -1;
      std::stringstream				ss;
      std::shared_ptr< Message::Room >		roomData = std::make_shared<Message::Room>();
      //Message::Entity				playerVector[MAX_PLAYER];

      roomData->_name = it.second->getName();
      roomData->_ip = it.second->getSocket()->getIp();
      roomData->_port = it.second->getSocket()->getPort();
      roomData->_nbPlayer = it.second->getNbPlayers();

      for (auto it2 : it.second->getPlayers())
	{
	  std::shared_ptr< Message::Entity >	entity = std::make_shared<Message::Entity>();
	  entity->_name = it2.second->getIp() + ":" + std::to_string(it2.second->getPort());
	  // entity->_pos_x = ;
	  // entity->_pos_y = ;
	  roomData->_players[++i] = *(entity.get());
	}   
      listOfRoom->_listOfRoom[++j] = *(roomData.get());    
    }
  ////
  
  ss.write((char *) listOfRoom.get(), sizeof( (listOfRoom.get()) ) );
  for (int y = 0; y <= j; y++)
    {
      ss.write((char *) &listOfRoom->_listOfRoom[y],
	       sizeof(listOfRoom->_listOfRoom[y]) );
      
      for (int x = 0; x < listOfRoom->_listOfRoom[y]._nbPlayer; x++)
	ss.write((char *) &listOfRoom->_listOfRoom[y]._players[x],
		 sizeof(listOfRoom->_listOfRoom[y]._players[x]) );
    }

  for (auto it : ss.str())
    {
      std::cout << "[" << it << "]";
    }
  std::cout << std::endl;
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

  char *						id;
  memcpy(&id, message->getData(), message->getSize());

  std::string						str(id);
  Room *						room = server->getRoomManager()->getRoomById(str);

  if (room)
    {
      if (room->getNbPlayers() < 4)
	{
	  int						i = -1;
	  std::stringstream				ss;
	  std::shared_ptr< Message::Room >		roomData = std::make_shared<Message::Room>();
	  Message::Entity				playerVector[MAX_PLAYER];

	  std::memset(&playerVector, 0, sizeof(Message::Entity) * MAX_PLAYER);
	  room->addPlayer(client);

	  roomData->_name = room->getName();
	  roomData->_ip = room->getSocket()->getIp();
	  roomData->_port = room->getSocket()->getPort();
	  roomData->_nbPlayer = room->getNbPlayers();

	  for (auto it : room->getPlayers())
	    {
	      std::shared_ptr< Message::Entity >	entity = std::make_shared<Message::Entity>();
	      entity->_name = it.second->getIp() + ":" + std::to_string(it.second->getPort());
	      // entity->_pos_x = ;
	      // entity->_pos_y = ;
	      playerVector[++i] = *(entity.get());
	    }

	  ss.write((char *) roomData.get(), sizeof(*(roomData.get())));	 
	  for (int x = 0; x <= i; x++)
	    ss.write((char *) &playerVector[x], sizeof(playerVector[x]));

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
