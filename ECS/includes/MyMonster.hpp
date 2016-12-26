//
// MyMonster.hpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Dec 13 19:33:48 2016 Thomas Billot
// Last update Thu Dec 22 21:20:37 2016 Thomas Billot
//

#pragma once

# include	<vector>
# include	<memory>
# include   <string>
# include	<iostream>
#include	"../includes/EntityManager.hpp"
#include	"../includes/SystemManager.hpp"
  
class								IMonster
{

public:

  virtual							~IMonster() = 0;
  virtual const std::vector<std::unique_ptr<IComponent> >	&getComponents() const = 0;
};

class				PositionComponent : public IComponent
{

  std::string		_name;
  
public:

  int				_x = 1;
  int				_y = 4;
  explicit			PositionComponent();
  virtual			~PositionComponent();
  virtual const std::string	&name();
  virtual void			debug() { std::cout << _x << " " << _y << std::endl; }
};

class				MeshComponent : public IComponent
{

  std::string		_name;
  
public:
  
  const std::string		_mesh;
  explicit			MeshComponent();
  virtual			~MeshComponent();
  virtual const std::string	&name();
  virtual void			debug() { std::cout << _mesh << std::endl; }
};

class				MassComponent : public IComponent
{

  std::string		_name;
  
public:

  int				_mass = 10;
  explicit			MassComponent();
  virtual			~MassComponent();
  virtual const std::string	&name();
  virtual void			debug() { std::cout << _mass << std::endl; }
};

class							MyMonster : public IMonster
{
  std::vector<std::unique_ptr<IComponent> >		_components;
  
public:
  explicit						MyMonster();
  virtual						~MyMonster();
  const std::vector<std::unique_ptr<IComponent> >	&getComponents() const;
};

typedef int (*ptrToF)(EntityManager &e, SystemManager &s);

template void EntityManager::addComponentType<MeshComponent>(std::string);

extern	"C"
{
  ptrToF	returnLoader();
}
