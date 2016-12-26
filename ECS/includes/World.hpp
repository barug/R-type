//
// GameEngine.hpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Fri Nov 25 15:08:25 2016 Thomas Billot
// Last update Fri Nov 25 17:16:45 2016 Thomas Billot
//

#ifndef			_GAMEENGINE_HPP_
# define		_GAMEENGINE_HPP_

# include		<map>
# include		<vector>
# include		"EntityManager.hpp"
# include		"TComponent.hpp"

class			GameEngine
{

public:

  GameEngine() : _entityManager() {}
  ~GameEngine() {}

  void			run(void);
  
private:

  EntityManager		_entityManager;
  
};

#endif			/* _GAMEENGINE_HPP_ */
