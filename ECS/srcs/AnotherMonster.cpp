//
// MyMonster.hpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Dec 13 19:33:48 2016 Thomas Billot
// Last update Thu Dec 22 18:15:05 2016 Thomas Billot
//

#include	"AnotherMonster.hpp"

extern "C"
{
  AnotherMonster *createAnotherMonster()
  {
    return new AnotherMonster;
  }
}

IComponent::~IComponent()
{}

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

AnotherMonster::AnotherMonster() : IMonster()
{
  IComponent *c1 = new PositionComponent;
  std::unique_ptr<IComponent> pC1(c1);
  _components.push_back(std::move(pC1));
  IComponent *c2 = new MeshComponent;
  std::unique_ptr<IComponent> pC2(c2);
  _components.push_back(std::move(pC2));
}

AnotherMonster::~AnotherMonster()
{}

const std::vector<std::unique_ptr<IComponent> >		&AnotherMonster::getComponents() const
{
  return _components;
}
