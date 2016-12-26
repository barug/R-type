# include	"CommandHandlerGame.hpp"

CommandHandlerGame::CommandHandlerGame() :
  _fptr{}
{}

CommandHandlerGame::~CommandHandlerGame()
{}

bool	CommandHandlerGame::execFuncByOperationCode(Room *room,
						Client& client,
						Message* message)
{
  auto it = _fptr.find((int)message->getOperationCode());
  if (it == _fptr.end())
    return false;
  return appelDeFonctionMembre(*this, it->second)(room, client, message);
}
