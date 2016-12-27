# include	<thread>
# include	<iostream>
# include	<unistd.h>
# include	<cstring>

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

void							RTypeServer::run()
{
  _networkHandler->getSocket().addFdSelect(STDIN_FILENO);

  while (_run)
    {
      int						fd = _networkHandler->getSocket().somethingToRead();

      if ( fd == STDIN_FILENO)
	{
	  char buff[5];
	  std::memset(&buff, 0, 5);
	  read(fd, buff, 4);
	  std::string quit(buff);
	  if (quit == "quit")
	    _run = false;
	}
      else if (fd != -1)
	{
	  const std::shared_ptr<ISocket::Datagram>	data = _networkHandler->getSocket().readSocket();
	  std::string					ipPort(data->_ip + ":" + std::to_string(data->_port));
	  Client *					clicli;

	  if (!(clicli = _networkHandler->getClientByKey(ipPort)))
	    clicli = _networkHandler->addClient(ipPort, data->_ip, data->_port);

	  std::unique_ptr<Message>			message = std::make_unique<Message>(*data);

	  _commandHandler->execFuncByOperationCode(this, *clicli, message.get());
	}
    }
  std::cout << "Bye" << std::endl;
}
