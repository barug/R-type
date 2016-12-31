# include	<iostream>
# include	<stdio.h>
# include	<cstring>
# include	<sstream>

# include	"Message.hpp"

Message::Message(int opCode, const std::string& ip, int port, void* data, int size) :
  _data((char*)data),
  _operationCode(opCode),
  _size(size),
  _ip(ip),
  _port(port),
  _datagram()
{
  std::cout << " [+] New Message Entity Create from Datas" << std::endl;
}

Message::Message(const ISocket::Datagram& data) :
  _data((char *)data._data + SIZE_HEADER),
  _operationCode(),
  _size(),
  _ip(data._ip),
  _port(data._port),
  _datagram(data)
{
  std::cout << " [+] New Message Entity Create from Datagram" << std::endl;

  char		size[4] = {data._data[0], data._data[1], data._data[2], data._data[3]};
  char		opCode[4] = {data._data[4], data._data[5], data._data[6], data._data[7]};

  std::memcpy(&_size, size, 4);
  std::memcpy(&_operationCode, opCode, 4);

  std::cout << "Datagram : [" << _ip
	    << "]:[" << _port
	    << "] => [\n";
  std::cout << "Header = [" << _size
	    << "] [" << _operationCode
	    << "]" << std::endl;
  // std::cout << "Data = [\n";
  // for (unsigned int i = 0; i < data._lenght; i++)
  //   printf("[%c]", data._data[i]);
  std::cout << "\n] ]" << std::endl;
}

Message::~Message()
{}

int	Message::getOperationCode() const
{
  return _operationCode;
}

int     Message::getSize() const
{
  return _size;
}

char *	Message::getData() const
{
  return _data;
}

const std::string&	Message::getIp() const
{
  return _ip;
}

int	Message::getPort() const
{
  return _port;
}

std::shared_ptr<ISocket::Datagram>	Message::createDatagram()
{
  if (_ip.empty())
    return nullptr;

  std::shared_ptr<ISocket::Datagram>	datagram = std::make_shared<ISocket::Datagram>();
  datagram->_ip = _ip;
  datagram->_port = _port;
  std::cout << _size << std::endl;
  memset(datagram->_data, 0, BUFFLEN); //check len

  Message::Header			header;
  header._size = _size;
  header._opCode = _operationCode;

  char *turlu = (char *)&header;

  for (int i = 0; i < SIZE_HEADER; ++i)
    datagram->_data[i] = turlu[i];
  for (int i = 0; i < _size; ++i)
    datagram->_data[SIZE_HEADER + i] = _data[i];

  datagram->_lenght = SIZE_HEADER + _size;

  std::cout << " [+] New Datagram is create from a Message Entity" << std::endl;
  std::cout << "Datagram : [" << datagram->_ip
	    << "]:[" << datagram->_port
	    << "] => [\n";

  std::cout << "Header = [" << header._size
	    << "] [" << header._opCode
	    << "]" << std::endl;
  // std::cout << "Data = [\n";
  // for (unsigned int i = 0; i < datagram->_lenght; i++)
  //   printf("[%c]", datagram->_data[i]);
  std::cout <<  "\n] ]" << std::endl;

  return datagram;
}
