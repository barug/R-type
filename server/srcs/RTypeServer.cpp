# include	<iostream>
#if defined (__UNIX__)
# include	<unistd.h>
# define _read read;
#elif defined(_WIN32) || defined (WIN32)
#include <io.h>
#endif
# include	"RTypeServer.hpp"

RTypeServer::RTypeServer(const int port) :
  _networkHandler(std::make_shared<NetworkHandler>(port)),
  _roomManager(std::make_shared<RoomManager>(_networkHandler)),
  _commandHandler(std::make_unique<CommandHandler>()),
  _run(true)
{}

RTypeServer::~RTypeServer()
{}

const NetworkHandler*  RTypeServer::getNetworkHandler() const
{
  return _networkHandler.get();
}

const std::shared_ptr<RoomManager>  RTypeServer::getRoomManager() const
{
  return _roomManager;
}

void		RTypeServer::checkInput()
{
  char		buff[5];
  int		r;

  r = _read(0, buff, 4);
  buff[r] = 0;

  std::string	quit(buff);
  if (quit == "quit")
    _run = false;
}

void						RTypeServer::checkSocket()
{
  const std::shared_ptr<ISocket::Datagram>	data = _networkHandler->getSocket().readSocket();
  std::string					ipPort(data->_ip + ":" + std::to_string(data->_port));
  Client *					clicli;

  if (!(clicli = _networkHandler->getClientByKey(ipPort)))
    clicli = _networkHandler->addClient(ipPort, data->_ip, data->_port);

  std::unique_ptr<Message>			message = std::make_unique<Message>(*data);

  _commandHandler->execFuncByOperationCode(this, *clicli, message.get());
}

void		RTypeServer::run()
{
  int		fd;
  _networkHandler->getSocket().addFdSelect(0);

  while (_run)
    {
      if ( ( fd = _networkHandler->getSocket().somethingToRead() ) == 0)
	this->checkInput();
      else if (fd != -1)
	this->checkSocket();
      _roomManager->checkRoom();
    }
  std::cout << "Bye" << std::endl;
}
