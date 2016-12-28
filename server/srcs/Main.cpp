# include	<iostream>
# include	<string>
# include	<memory>

# include	"RTypeServer.hpp"

int	Usage(char *name)
{
  std::cerr << "Usage:\n\t./" << name << " port " << std::endl;
  return 1;
}

bool	checkArgs(int ac, char **av)
{
  if (ac == 2)
    {
      for (int i = 0; av[1][i]; i++)
	if (av[1][i] < '0' || av[1][i] > '9')
	return false;
      return true;
    }
  return false;
}

int					main(int ac, char **av)
{
  if (checkArgs(ac, av))
    try
      {
	std::unique_ptr<RTypeServer>	server = std::make_unique<RTypeServer> (atoi(av[1]));
	server->run();
	return 0;
      }
    catch (const std::string & e)
      {
	std::cerr << e << std::endl;
	return -1;
      }
  return Usage(av[0]);
}
