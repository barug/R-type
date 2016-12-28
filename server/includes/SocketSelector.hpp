#ifndef		__SOCKETSELECTOR_HPP__
# define	__SOCKETSELECTOR_HPP__

# include	<sys/time.h>
# include	<sys/types.h>
# include	<unistd.h>

# include	<map>
# include	<list>

class		SocketSelector
{
public:

  explicit SocketSelector(int fdSocket);
  ~SocketSelector();

  struct		Select
  {
    bool		keyboard;
    bool		socket;
  };

  Select	somethingToRead();

private:

  struct timeval	_tv;
  fd_set		_writeFd;
  fd_set		_readFd;
  int			_maxFd;
  int			_fdSocket;

  void			setFds();
  Select		checkFds();

};

#endif		/* !__SOCKETSELECTOR_HPP__ */
