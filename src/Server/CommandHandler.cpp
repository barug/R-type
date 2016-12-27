# include	<iostream>
# include	<sstream>

# include	<string.h> // memcpy; but stringstream is better nah ?

# include	"CommandHandler.hpp"

CommandHandler::CommandHandler() :
  _fptr{ {101, &CommandHandler::logInUser },
	 {102, &CommandHandler::createRoom },
	 {103, &CommandHandler::joinRoom } }
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

bool						CommandHandler::logInUser(RTypeServer *server,
									  Client &client,
									  Message *)
{
  std::cout << " \033[1;32m[+] Action 101 is managed\033[0m" << std::endl;

  char *	salut = "salut";
  this->sendMessage(server, 1, client.getIp(), client.getPort(), salut, (5 * sizeof(char)));
  //  this->sendMessage(server, 1, client.getIp(), client.getPort());

  Message::ListOfRoom *	listOfRoom
    = new Message::ListOfRoom();
  // fill ListOfRoom
  listOfRoom->_nbRoom = 0;
  listOfRoom->_listOfRoom = NULL; // init anotherway

  this->sendMessage(server, 2, client.getIp(), client.getPort(), listOfRoom);

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

bool					CommandHandler::createRoom(RTypeServer *server,
								   Client &client,
								   Message *message)
{
  std::cout << " \033[1;32m[+] Action 102 is managed\033[0m" << std::endl;

  // Review the way to convert data
  char					*id;
  memcpy(&id, message->getData(), message->getSize());
  std::string				str(id);
  std::cout << id << std::endl;

  if (!this->checkId(str))
    this->sendMessage(server, 204, client.getIp(), client.getPort());
  else if (!server->getRoomManager()->getRoomById(id))
    {
      if (server->getRoomManager()->getRoomNumber() == MAX_ROOM)
	this->sendMessage(server, 203, client.getIp(), client.getPort());
      server->getRoomManager()->createRoom(str);
      this->sendMessage(server, 2, client.getIp(), client.getPort());
      this->joinRoom(server, client, message);
    }
  else
    this->sendMessage(server, 205, client.getIp(), client.getPort());

  return false;
}

bool					CommandHandler::joinRoom(RTypeServer *server,
								 Client &client,
								 Message *message)
{
  std::cout << " \033[1;32m[+] Action 103 is managed\033[0m" << std::endl;

  // Review the way to convert data
  char *				id;
  memcpy(&id, message->getData(), message->getSize());
  std::string				str(id);
  Room *				room = server->getRoomManager()->getRoomById(str);

  if (room)
    {
      if (room->getNbPlayers() < 4)
	{
	  room->addPlayer(client);

	  // create Message::Room
	  // append IpRoom:PortRoom
	  // sendToTheClient so he co on the new socket
	  // this->sendMessage(server, 4, client.getIp(), client.getPort(), data);
	  // data = Struct Room + room->getIp() + room->getPort()

	  return true;
	}
      else
	this->sendMessage(server, 202, client.getIp(), client.getPort());
    }
  else
    this->sendMessage(server, 201, client.getIp(), client.getPort());
  return false;
}
