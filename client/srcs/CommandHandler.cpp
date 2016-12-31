# include	<iostream>
# include	<cstring>
# include	<sstream>

# include	"../includes/CommandHandler.hpp"

CommandHandler::CommandHandler() :
  _fptr { { 1, &CommandHandler::userLoggedIn },
	  { 2, &CommandHandler::listOfRoom },
	  { 3, &CommandHandler::roomCreated },
	  { 4, &CommandHandler::roomJoined },
	  { 5, &CommandHandler::gameStarted },
	  { 202, &CommandHandler::roomDontExist },
	  { 201, &CommandHandler::numberPlayerMax },
	  { 203, &CommandHandler::maxRoom },
	  { 204, &CommandHandler::illegaleId },
	  { 205, &CommandHandler::roomExist }
	}
{
}

CommandHandler::~CommandHandler()
{}

bool	CommandHandler::execFuncByOperationCode(RTypeClient * client, Message * message, int sock)
{
  auto	it = _fptr.find(message->getOperationCode());

  if (it == _fptr.end())
    return false;
  return appelDeFonctionMembre(*this, it->second)(client, message, sock);
}

void				CommandHandler::sendGameMessage(RTypeClient *client,
							    int opCode,
								void * data,
								int size)
{
  std::cout << " \033[1;33m[+] Reaction in Game" << ((opCode < 100) ? " 00" : " ");
  std::cout << opCode;
  std::cout << " is invoque\033[0m" << std::endl;

  std::string			ip = client->getNetworkHandler()->getSocketGame().getIpServer();
  int				port = client->getNetworkHandler()->getSocketGame().getPortServer();

  std::cout << "IP="  << ip << " port=" << port << std::endl;
  std::shared_ptr< Message >	message = std::make_shared< Message >(opCode, ip, port, data, size);
  client->getNetworkHandler()->getSocketGame().writeSocket(*(message->createDatagram()));
}

void				CommandHandler::sendMessage(RTypeClient *client,
							    int opCode,
							    void * data,
							    int size)
{
  std::cout << " \033[1;33m[+] Reaction in Game" << ((opCode < 100) ? " 00" : " ");
  std::cout << opCode;
  std::cout << " is invoque\033[0m" << std::endl;

  std::string			ip = client->getNetworkHandler()->getSocket().getIpServer();
  int				port = client->getNetworkHandler()->getSocket().getPortServer();

  std::cout << "IP="  << ip << " port=" << port << std::endl;
  std::shared_ptr< Message >	message = std::make_shared< Message >(opCode, ip, port, data, size);
  client->getNetworkHandler()->getSocket().writeSocket(*(message->createDatagram()));
}

bool	CommandHandler::userLoggedIn(RTypeClient *, Message *message, int sock)
{
  std::cout << " \033[1;32m[+] Action 001 is managed\033[0m" << std::endl;

  return true;
}

bool			CommandHandler::listOfRoom(RTypeClient *client, Message *message, int sock)
{
  std::cout << " \033[1;32m[+] Action 002 is managed\033[0m" << std::endl;

  std::stringstream    ss;

  Message::ListOfRoom	*room;

  room = (Message::ListOfRoom *) message->getData();

  std::cout << "nb Rooms= " << room->_nbRoom << std::endl;

  for (int i = 0; i < room->_nbRoom; i++)
    {
      std::cout << "Room [" << i << "]" << std::endl;
      std::cout << room->_listOfRoom[i]._name << std::endl;
    }
  return true;
}

bool	CommandHandler::roomCreated(RTypeClient *client, Message *message, int sock)
{
  std::cout << " \033[1;32m[+] Action 003 is managed\033[0m" << std::endl;

  std::cout << "Room Succeffuly Created" << std::endl;

  return true;
}

bool		CommandHandler::roomJoined(RTypeClient *client, Message *message, int sock)
{
  std::cout << " \033[1;32m[+] Action 004 is managed\033[0m" << std::endl;

  Message::Room	*room;

  room = (Message::Room *)message->getData();
  
  std::cout << "Please connect on the new port :\n\t"
	    << room->_port << std::endl;
  std::cout << room->_name << std::endl;
  
  client->getNetworkHandler()->setSocketGame(room->_port);

  //  Message::Room	tmp = {};

  //  std::stringstream	ss;

  // int i = room->_nbPlayer - 1;

  //  std::string str(room->_players[i]._name);

  // i = -1;
  // for (auto car : str)
  //   tmp._name[++i] = car;
  
  // ss.clear();
  // ss.write((char*)&tmp, sizeof(tmp));

  const char *oldPort = std::to_string(client->getNetworkHandler()->getSocket().getPort()).c_str();

  this->sendGameMessage(client, 105, (void*)oldPort, (int)std::strlen(oldPort));

  const char *newPort =  (std::to_string(client->getNetworkHandler()->getSocketGame().getPort())).c_str();
  this->sendMessage(client, 105, (void*)newPort, (int)std::strlen(newPort));

  return true;
}

bool	CommandHandler::roomDontExist(RTypeClient *client, Message *message, int sock)
{
  std::cout << " \033[1;31m[+] Action 201 is managed\033[0m" << std::endl;

  std::cout << "Cannot join that room; the roomId "
	    << "doesn't match any room."
	    << std::endl;

  return true;
}

bool	CommandHandler::numberPlayerMax(RTypeClient *client, Message *message, int sock)
{
  std::cout << " \033[1;31m[+] Action 202 is managed\033[0m" << std::endl;

  std::cout << "Cannot join that room new room; the number "
	    << "of player will execed the capacity of the room"
	    << std::endl;

  return true;
}

bool	CommandHandler::maxRoom(RTypeClient *client, Message *message, int sock)
{
  std::cout << " \033[1;31m[+] Action 203 is managed\033[0m" << std::endl;

  std::cout << "Cannot create a new room; the number "
	    << "of room will execed the capacity of the server"
	    << std::endl;

  return true;
}

bool	CommandHandler::illegaleId(RTypeClient *client, Message *message, int sock)
{
  std::cout << " \033[1;31m[+] Action 204 is managed\033[0m" << std::endl;

  std::cout << "The room name contain illegale character;"
	    << "make sure to only use letter and digit (a-z, A-Z, 0-9)"
	    << std::endl;

  return true;
}

bool	CommandHandler::roomExist(RTypeClient *client, Message *message, int sock)
{
  std::cout << " \033[1;31m[+] Action 203 is managed\033[0m" << std::endl;

  std::cout << "Cannot create a room with this id;"
	    << " id already in use"
	    << std::endl;

  return true;
}

bool	CommandHandler::gameStarted(RTypeClient *client, Message *message, int sock)
{
  std::cout << " \033[1;31m[+] Action 005 is managed\033[0m" << std::endl;

  client->setGameStarted(true);
  return true;
}
