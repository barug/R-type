//
// MyMonster.hpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Dec 13 19:33:48 2016 Thomas Billot
// Last update Fri Dec 23 18:43:21 2016 Thomas Billot
//

#include	"MyMonster.hpp"
#include	"../includes/EntityManager.hpp"
#include	"../includes/SystemManager.hpp"

int loadGameLibData(EntityManager &e, SystemManager &s)
{
  e.addComponentType<PositionComponent>("PositionComponent");
  e.addComponentType<MeshComponent>("MeshComponent");
  e.addComponentType<MassComponent>("MassComponent");
  e.addEntityType("MyMonster", 10);
  return 0;		       	
}

extern "C"
{
  ptrToF		returnLoader()
  {
    return &loadGameLibData;
  }
}
