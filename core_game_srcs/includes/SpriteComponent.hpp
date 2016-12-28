#ifndef         __SPRITE_COMPONENT_HPP_
# define        __SPRITE_COMPONENT_HPP_

# include       "IComponent.hpp"

class           SpriteComponent : public IComponent
{
  std::string   _path;

public:
  SpriteComponent(const std::string &path);
  virtual ~SpriteComponent();
  virtual const std::string     name() = 0;
  const std::string&            getPath() const;
};

#endif          // !__SPRITE_COMPONENT_HPP_
