//
// EntityFactory.hpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Mon Dec 19 17:32:40 2016 Thomas Billot
// Last update Mon Dec 19 17:55:57 2016 Thomas Billot
//

#pragma once

class				EntityFactory
{

public:
  
  explicit			EntityFactory();
				~EntityFactory();

  void				addMonsterToFactory(const std::string &name, IMonster *);
  void				removeMonsterFromFactory(const std::string &name);

private:

  EntityFactory(const EntityFactory &lhs);
  EntityFactory			operator=(EntityFactory &lhs);
};
