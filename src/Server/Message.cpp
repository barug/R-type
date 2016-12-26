# include	<iostream>
# include	<stdio.h>
# include	<cstring>

# include	"Message.hpp"

Message::Message(int opCode, const std::string& ip, int port, void* data, int size) :
  _data((char*)data),
  _operationCode(opCode),
  _size(size),
  _ip(ip),
  _port(port),
  _datagram()
{
  if (size)
    std::cout << (char*) _data << std::endl;
  std::cout << " [+] New Message Entity Create from Datas" << std::endl;
}

Message::Message(const ISocket::Datagram& data) :
  _data((char *)data._data),
  _operationCode(),
  _size(data._lenght),
  _ip(data._ip),
  _port(data._port),
  _datagram(data)
{
  std::cout << " [+] New Message Entity Create from Datagram" << std::endl;

  char		size[4] = {data._data[0], data._data[1], data._data[2], data._data[3]};
  char		opCode[4] = {data._data[4], data._data[5], data._data[6], data._data[7]};

  int		size2;
  int		opCode2;
  char		*data2;

  std::memcpy(&size2, size, 4);
  std::memcpy(&opCode2, opCode, 4);

  std::memset(&data2, 0, size2 + 1);
  std::memcpy(&data2, &(data._data[8]), size2);
  _data = data2;    
  // _data = (char*)data._data;
  // _data += SIZE_HEADER;

  std::cout << "Datagram : [" << data._ip
	    << "]:[" << data._port
	    << "] => [\n";
  std::cout << "Header = [" << size2
	    << "] [" << opCode2
	    << "]" << std::endl;
  std::cout << "Data = [ ";
  if (size2)
    std::cout << _data;
  std::cout << " ]\n]" << std::endl;
  _operationCode = opCode2;
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

  #include <sstream>

std::shared_ptr<ISocket::Datagram>	Message::createDatagram() 
{
  if (_ip.empty())
    return nullptr;

  std::shared_ptr<ISocket::Datagram>	datagram = std::make_shared<ISocket::Datagram>();
  datagram->_ip = _ip;
  datagram->_port = _port;
  memset(datagram->_data, 0, BUFFLEN); //check len

  Message::Header			header;
  header._size = _size;
  header._opCode = _operationCode;

  std::stringstream		        ss;

  ss.clear();
  ss.write((char*)(&header), sizeof(header));
  ss.write((char*)(&_data), _size);
  
  char	c;
  int	j = 0;
  while (ss >> c)
    datagram->_data[j++] = c;
  datagram->_lenght = SIZE_HEADER + _size;

  std::cout << " [+] New Datagram is create from a Message Entity" << std::endl;
  std::cout << "Datagram : [" << datagram->_ip
	    << "]:[" << datagram->_port
	    << "] => [\n";  
  char		size[4] = {datagram->_data[0], datagram->_data[1], datagram->_data[2], datagram->_data[3]};
  char		opCode[4] = {datagram->_data[4], datagram->_data[5], datagram->_data[6], datagram->_data[7]};
  int		size2;
  int		opCode2;
  char		*data2;

  std::memset(&data2, 0, _size + 1);
  std::memcpy(&data2, &(datagram->_data[8]), _size);
  // _data = datagram->_data;
  // _data += SIZE_HEADER;
  std::memcpy(&size2, size, 4);
  std::memcpy(&opCode2, opCode, 4);
  std::cout << "Header = [" << size2
	    << "] [" << opCode2
	    << "]" << std::endl;
  std::cout << "Data = [ ";
  if (header._size)
    std::cout << data2;
    // std::cout << _data;
  std::cout <<  " ]\n]" << std::endl;

  return datagram;
}
