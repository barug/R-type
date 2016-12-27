# include	<iostream>
# include	<cstring>

# include	"CommandHandler.hpp"

CommandHandler::CommandHandler() :
  _fptr { { 1, &CommandHandler::userLoggedIn },
	  { 2, &CommandHandler::listOfRoom },
	  { 3, &CommandHandler::roomCreated },
	  { 203, &CommandHandler::maxRoom },
	  { 204, &CommandHandler::illegaleId },
	  { 205, &CommandHandler::roomExist }
	}
{}

CommandHandler::~CommandHandler()
{}

bool	CommandHandler::execFuncByOperationCode(RTypeClient * client, Message * message)
{
  auto it = _fptr.find(message->getOperationCode());

  if (it == _fptr.end())
    return false;
  return appelDeFonctionMembre(*this, it->second)(client, message);
}

bool		CommandHandler::userLoggedIn(RTypeClient *, Message *message)
{
  std::cout << " \033[1;31m[+] Action 001 is managed\033[0m" << std::endl;

  char		data[BUFFLEN];
  std::memset(&data, 0, BUFFLEN);
  std::memcpy(&data, message->getData(), message->getSize());
  std::cout << "Server say :" << data << std::endl;

  return true;
}

bool	CommandHandler::listOfRoom(RTypeClient *client, Message *message)
{
  std::cout << " \033[1;31m[+] Action 002 is managed\033[0m" << std::endl;

  Message::ListOfRoom rooms;
  std::memcpy(&rooms, message->getData(), message->getSize());

  return true;
}

bool	CommandHandler::roomCreated(RTypeClient *client, Message *message)
{
  std::cout << " \033[1;31m[+] Action 003 is managed\033[0m" << std::endl;

  std::cout << "Room Succeffuly Created" << std::endl;

  return true;
}

bool	CommandHandler::maxRoom(RTypeClient *client, Message *message)
{
  std::cout << " \033[1;31m[+] Action 003 is managed\033[0m" << std::endl;

  std::cout << "Cannot create a new room; the number "
	    << "of room will execed the capacity of the server"
	    << std::endl;

  return true;
}

bool	CommandHandler::illegaleId(RTypeClient *client, Message *message)
{
  std::cout << " \033[1;31m[+] Action 204 is managed\033[0m" << std::endl;

  std::cout << "The room name contain illegale character;"
	    << "make sure to only use letter and digit (a-z, A-Z, 0-9)"
	    << std::endl;

  return true;
}

bool	CommandHandler::roomExist(RTypeClient *client, Message *message)
{
  std::cout << " \033[1;31m[+] Action 204 is managed\033[0m" << std::endl;

  std::cout << "Cannot creqte a room with this id;"
	    << " id already in use"
	    << std::endl;

  return true;
}
