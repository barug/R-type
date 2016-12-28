#ifndef         __SPRITE_COMPONENT_HPP_
# define        __SPRITE_COMPONENT_HPP_

# include       "IComponent.hpp"

class           SpriteComponent : public IComponent
{
  // static const std::string	name = ;
  std::string			_path;
  
public:
  SpriteComponent();
  virtual ~SpriteComponent();
  virtual const std::string     name();
  const std::string&            getPath() const;
  void				setPath(const std::string &path);
};

#endif          // !__SPRITE_COMPONENT_HPP_
