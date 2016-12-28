# include	<thread>
# include	<iostream>

# include	<memory>

# include	"RTypeClient.hpp"
# include	"Message.hpp"

RTypeClient::RTypeClient() :
  _networkHandler(std::make_shared<NetworkHandler>()),
  _commandHandler(std::make_unique<CommandHandler>())
{}

RTypeClient::RTypeClient(const std::string ip, const int port) :
  _networkHandler(std::make_shared<NetworkHandler>(ip, port)),
  _commandHandler(std::make_unique<CommandHandler>())
{
  // create the co cmd
  std::unique_ptr< Message >	message =
    std::make_unique< Message >(101,
                                _networkHandler->getSocket().getIpServer(),
                                _networkHandler->getSocket().getPortServer());
  // write  the co cmd
  _networkHandler->getSocket().writeSocket(*message->createDatagram());
}

RTypeClient::~RTypeClient()
{}

const NetworkHandler*  RTypeClient::getNetworkHandler() const
{
  return _networkHandler.get();
}

void    RTypeClient::connectToServer(const std::string &ip, const int port)
{
  _networkHandler->getSocket().connectToServer(ip, port);
  std::unique_ptr< Message >	message =
    std::make_unique< Message >(101,
                                _networkHandler->getSocket().getIpServer(),
                                _networkHandler->getSocket().getPortServer());
  _networkHandler->getSocket().writeSocket(*message->createDatagram());
}

void	RTypeClient::run()
{
  if (_networkHandler->getSocket().somethingToRead())
    {
      const std::shared_ptr<ISocket::Datagram>	data = _networkHandler->getSocket().readSocket();

      Message*			message = new Message(*data);

      _commandHandler->execFuncByOperationCode(this, message);
    }
}
