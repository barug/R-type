# include	<iostream>
# include	"CommandHandlerGame.hpp"
# include	"Client.hpp"

CommandHandlerGame::CommandHandlerGame() :
  _fptr{{109, &CommandHandlerGame::userJoinedGame}}
{}

CommandHandlerGame::~CommandHandlerGame()
{}

bool				CommandHandlerGame::execFuncByOperationCode(Room *room,
						    Message* message)
{
  auto it = _fptr.find((int)message->getOperationCode());
  if (it == _fptr.end())
    return false;
  return appelDeFonctionMembre(*this, it->second)(room, message);
}

void				CommandHandlerGame::sendGameMessage(Room *room,
								    const std::string & ip,
								    const int port,
								    const int opCode,
								    void * data,
								    const int size)
{
  std::cout << " \033[1;33m[+] Reaction in Game" << ((opCode < 100) ? " 00" : " ");
  std::cout << opCode;
  std::cout << " is invoque\033[0m" << std::endl;

  // std::shared_ptr< Message >	message = std::make_shared< Message >(opCode, room->getSocket()->getIp(), room->getSocket()->getPort(), data, size);
  // room->getSocket()->writeSocket(*(message->createDatagram()));
}

bool			CommandHandlerGame::userJoinedGame(Room *room, Message *message)
{
  std::cout << " \033[1;32m[+] Action 109 is managed\033[0m" << std::endl;

  int port = atoi(message->getData());
  std::cout << "Have to link " << port << " w/ " << message->getPort() << std::endl;
  //decompile the messgae;
  //modifie the old clicos;

  // if (_playersGameId.size() < 2)
  //   {
  //     Message::Room				*room = (Message::Room *)message->getData();
  //     _playersGameId.emplace(ipPort, room->_name);

  //     std::size_t found = ipPort.find(':');

  //     std::string ip = ipPort.substr(0, found);
  //     std::cout << ip << std::endl;

  //     std::string tmpPort = ipPort.substr(found + 1);
  //     std::stringstream ss;
  //     int		port;

  //     ss << tmpPort;
  //     ss >> port;
  //     _gameEngine.postImmediateMessage(ServerMessages::ADD_CLIENT, new std::pair<std::string, int>(data->_ip, data->_port));
  // }


  return true;
}
