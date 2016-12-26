# include	<iostream>
# include	<sstream>

# include	"CommandHandler.hpp"

CommandHandler::CommandHandler() :
  _fptr{ {1, &CommandHandler::userLoggedIn },
	 {2, &CommandHandler::listOfRoom } }
{}

CommandHandler::~CommandHandler()
{}

bool	CommandHandler::execFuncByOperationCode(RTypeClient * client, Message * message)
{
  // std::cout << message->getOperationCode() << std::endl;

  auto it = _fptr.find(message->getOperationCode());

  if (it == _fptr.end())
    return false;
  return appelDeFonctionMembre(*this, it->second)(client, message);
}

bool	CommandHandler::userLoggedIn(RTypeClient *, Message *)
{
  std::cout << " \033[1;31m[+] Action 001 is managed\033[0m" << std::endl;
  return true;
}

bool	CommandHandler::listOfRoom(RTypeClient *client, Message *message)
{
  std::cout << " \033[1;31m[+] Action 002 is managed\033[0m" << std::endl;
  return true;
}
