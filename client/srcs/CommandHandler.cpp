# include	<iostream>
# include	<cstring>
# include	<sstream>

# include	"CommandHandler.hpp"

CommandHandler::CommandHandler() :
  _fptr { { 1, &CommandHandler::userLoggedIn },
	  { 2, &CommandHandler::listOfRoom },
	  { 3, &CommandHandler::roomCreated },
	  { 4, &CommandHandler::roomJoined },
	  { 202, &CommandHandler::roomDontExist },
	  { 201, &CommandHandler::numberPlayerMax },
	  { 203, &CommandHandler::maxRoom },
	  { 204, &CommandHandler::illegaleId },
	  { 205, &CommandHandler::roomExist }
	}
{}

CommandHandler::~CommandHandler()
{}

bool	CommandHandler::execFuncByOperationCode(RTypeClient * client, Message * message)
{
  auto	it = _fptr.find(message->getOperationCode());

  if (it == _fptr.end())
    return false;
  return appelDeFonctionMembre(*this, it->second)(client, message);
}

bool	CommandHandler::userLoggedIn(RTypeClient *, Message *message)
{
  std::cout << " \033[1;32m[+] Action 001 is managed\033[0m" << std::endl;

  return true;
}

bool			CommandHandler::listOfRoom(RTypeClient *client, Message *message)
{
  std::cout << " \033[1;32m[+] Action 002 is managed\033[0m" << std::endl;

  std::stringstream	*ss = new std::stringstream (message->getData());
  Message::ListOfRoom	rooms;

  std::memcpy(&rooms, ss->str().c_str(), ss->str().size());
  std::cout << "Their is " << rooms._nbRoom << " rooms" << std::endl;

  return true;
}

bool	CommandHandler::roomCreated(RTypeClient *client, Message *message)
{
  std::cout << " \033[1;32m[+] Action 003 is managed\033[0m" << std::endl;

  std::cout << "Room Succeffuly Created" << std::endl;

  return true;
}

bool		CommandHandler::roomJoined(RTypeClient *client, Message *message)
{
  std::cout << " \033[1;32m[+] Action 004 is managed\033[0m" << std::endl;

  Message::Room	room;
  std::memcpy(&room, (void *)message->getData(), message->getSize());

  std::cout << "Please connect on the new port :\n\t"
	    << room._port << std::endl;

  return true;
}

bool	CommandHandler::roomDontExist(RTypeClient *client, Message *message)
{
  std::cout << " \033[1;31m[+] Action 201 is managed\033[0m" << std::endl;

  std::cout << "Cannot join that room; the roomId "
	    << "doesn't match any room."
	    << std::endl;

  return true;
}

bool	CommandHandler::numberPlayerMax(RTypeClient *client, Message *message)
{
  std::cout << " \033[1;31m[+] Action 202 is managed\033[0m" << std::endl;

  std::cout << "Cannot join that room new room; the number "
	    << "of player will execed the capacity of the room"
	    << std::endl;

  return true;
}

bool	CommandHandler::maxRoom(RTypeClient *client, Message *message)
{
  std::cout << " \033[1;31m[+] Action 203 is managed\033[0m" << std::endl;

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
  std::cout << " \033[1;31m[+] Action 203 is managed\033[0m" << std::endl;

  std::cout << "Cannot create a room with this id;"
	    << " id already in use"
	    << std::endl;

  return true;
}
