//
// rtype
//
# include		<iostream>
# include       "Core.hpp"

int	       main(int ac, char **av)
{
  try
    {
      Core          core(ac, av);
      core.gameLoop();
    }
  catch (const std::exception &e)
    {
      std::cout << e.what() << std::endl;
    }
  return (0);
}
