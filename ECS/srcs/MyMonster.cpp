//
// MyMonster.hpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Dec 13 19:33:48 2016 Thomas Billot
// Last update Thu Dec 22 22:52:40 2016 Thomas Billot
//

#include	"MyMonster.hpp"
#include	"../includes/EntityManager.hpp"
#include	"../includes/SystemManager.hpp"

IMonster::~IMonster()
{}

PositionComponent::PositionComponent()
  : _name("PositionComponent")
{
  std::cout << "[+] PositionComponent" << std::endl;
}

PositionComponent::~PositionComponent()
{}

const std::string	&PositionComponent::name()
{
  return _name;
}

MeshComponent::MeshComponent()
  : _mesh(),
    _name("MeshComponent")
{
  std::cout << "[+] MeshComponent" << std::endl;
}

const std::string	&MeshComponent::name()
{
  return _name;
}

MeshComponent::~MeshComponent()
{
  std::cout << "[-] MeshComponent" << std::endl;
}

MassComponent::MassComponent() : _name("MassComponent")
{
  std::cout << "[+] MassComponent" << std::endl;
}

MassComponent::~MassComponent()
{}

const std::string	&MassComponent::name()
{
  return _name;
}

MyMonster::MyMonster() : IMonster()
{
  IComponent *c1 = new PositionComponent;
  std::unique_ptr<IComponent> pC1(c1);
  _components.push_back(std::move(pC1));
  IComponent *c2 = new MeshComponent;
  std::unique_ptr<IComponent> pC2(c2);
  _components.push_back(std::move(pC2));
  IComponent *c3 = new MassComponent;
  std::unique_ptr<IComponent> pC3(c3);
  _components.push_back(std::move(pC3));
}

MyMonster::~MyMonster()
{}

const std::vector<std::unique_ptr<IComponent> >		&MyMonster::getComponents() const
{
  return _components;
}

int loadGameLibData(EntityManager &e, SystemManager &s)
{
  e.addComponentType<MeshComponent>("MeshComponent");
  e.addComponentType<PositionComponent>("PositionComponent");
  e.addComponentType<MassComponent>("MassComponent");
  return 0;		       	
}

extern "C"
{
  ptrToF		returnLoader()
  {
    return &loadGameLibData;
  }
}
