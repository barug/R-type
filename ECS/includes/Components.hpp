#pragma once

#include	"IComponent.hpp"

class				MeshComponent : public IComponent
{

  std::string		_name = "MeshComponent";
  
public:
  
  const std::string		_mesh;
  explicit			MeshComponent() {}
  virtual			~MeshComponent() {}
  virtual const std::string	&name() { return _name; }
  virtual void			debug() { std::cout << _mesh << std::endl; }
};

class			        PositionComponent : public IComponent
{

  std::string		_name = "PositionComponent";
  
public:

  int				_x;
  int				_y;
  explicit			PositionComponent() : _x(0), _y(0) {}
  virtual			~PositionComponent() {}
  virtual const std::string	&name() { return _name; }
  virtual void			debug() { std::cout << _x << std::endl; }
};

class				MassComponent : public IComponent
{

  std::string		_name = "MassComponent";
  
public:

  int				_mass;
  explicit			MassComponent() : _mass(10) {}
  virtual			~MassComponent() {}
  virtual const std::string	&name() { return _name;}
  virtual void			debug() { std::cout << _mass << std::endl; }
};

