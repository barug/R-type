# include	<sys/time.h>
# include	<sys/types.h>
# include	<unistd.h>
# include	<map>

# include	<iostream>

# include	"SocketSelector.hpp"

SocketSelector::SocketSelector(int fdSocket) :
  _tv(),
  _writeFd(),
  _readFd(),
  _maxFd(),
  _fdSocket(fdSocket)
{
  _tv.tv_usec = 0;
  _tv.tv_sec = 1;
}

SocketSelector::~SocketSelector()
{}

void		SocketSelector::setFds()
{
  FD_ZERO(&_writeFd);
  FD_ZERO(&_readFd);

  FD_SET(_fdSocket, &_readFd);
  FD_SET(STDIN_FILENO, &_readFd);

  _maxFd = _fdSocket > STDIN_FILENO ? _fdSocket : STDIN_FILENO;

  if (!_tv.tv_usec)
    _tv.tv_sec = 5;
}

SocketSelector::Select		SocketSelector::checkFds()
{
  SocketSelector::Select	select;

  select.socket = (FD_ISSET(_fdSocket, &_readFd)) ? true : false;
  select.keyboard = (FD_ISSET(STDIN_FILENO, &_readFd)) ? true : false;

  return select;
}

SocketSelector::Select	SocketSelector::somethingToRead()
{
  this->setFds();
  if (select(_maxFd + 1, &_readFd,
	     &_writeFd, NULL, &_tv) == -1 )
    { /* maybe some clean of code there */ }
  return this->checkFds();
}
