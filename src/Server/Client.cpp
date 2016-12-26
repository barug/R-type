# include	"Client.hpp"

Client::Client(const std::string& ip, int port) :
  _ip(ip),
  _port(port)
{}

Client::~Client()
{}

void	Client::setIp(const std::string& ip)
{
  _ip = ip;
}

bool	Client::operator==(Client const &clicli)
{
  return (_ip == clicli.getIp() && _port == clicli.getPort()) ? true : false;
}

const std::string&	Client::getIp() const
{
  return _ip;
}

void	Client::setPort(int port)
{
  _port = port;
}

int	Client::getPort() const
{
  return _port;
}
