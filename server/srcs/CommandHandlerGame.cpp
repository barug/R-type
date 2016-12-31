# include	<iostream>
# include	"CommandHandlerGame.hpp"
# include	"Client.hpp"

CommandHandlerGame::CommandHandlerGame() :
  _fptr{{109, &CommandHandlerGame::userJoinedGame}}
{}

CommandHandlerGame::~CommandHandlerGame()
{}

bool				CommandHandlerGame::execFuncByOperationCode(Room *room,
						    Client& client,
						    Message* message)
{
  auto it = _fptr.find((int)message->getOperationCode());
  if (it == _fptr.end())
    return false;
  return appelDeFonctionMembre(*this, it->second)(room, client, message);
}

void				CommandHandlerGame::sendGameMessage(Room *room,
								int opCode,
								void * data,
								int size)
{
  std::cout << " \033[1;33m[+] Reaction in Game" << ((opCode < 100) ? " 00" : " ");
  std::cout << opCode;
  std::cout << " is invoque\033[0m" << std::endl;

  std::shared_ptr< Message >	message = std::make_shared< Message >(opCode, room->getSocket()->getIp(), room->getSocket()->getPort(), data, size);
  room->getSocket()->writeSocket(*(message->createDatagram()));
}

bool			CommandHandlerGame::userJoinedGame(Room *, Client &, Message *)
{
  std::cout << " \033[1;32m[+] Action 109 is managed\033[0m" << std::endl;
  return true;
}
