#ifndef         __SPRITE_COMPONENT_HPP_
# define        __SPRITE_COMPONENT_HPP_

# include       "IComponent.hpp"

class           SpriteComponent : public IComponent
{
  std::string			_path;
  
public:

  static const std::string	name;
  
  SpriteComponent();
  virtual ~SpriteComponent();
  virtual const std::string     getName();
  const std::string&            getPath() const;
  void				setPath(const std::string &path);
};

#endif          // !__SPRITE_COMPONENT_HPP_
