//
// GameEngine.hpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Fri Nov 25 15:08:25 2016 Thomas Billot
// Last update Wed Dec 21 18:48:34 2016 Thomas Billot
//

#ifndef			_GAMEENGINE_HPP_
# define		_GAMEENGINE_HPP_

# include		<map>
# include		<vector>
# include		"EntityManager.hpp"
# include		"SystemManager.hpp"
# include		"ASystem.hpp"
# include		"MessageBus.hpp"

class			GameEngine
{

public:

  GameEngine(std::string libsDir = "");
  ~GameEngine();

  void			loadLib(std::string libPath);
  int			run(void);
  void			update(void);
  
private:

  MessageBus		_messageBus;  
  EntityManager		_entityManager;
  SystemManager		_systemManager;
  
};

#endif			/* _GAMEENGINE_HPP_ */
