# include       "SpriteComponent.hpp"

SpriteComponent::SpriteComponent()
{}

SpriteComponent::~SpriteComponent()
{}

const std::string               SpriteComponent::name()
{
  return "SpriteComponent";
}

const std::string&              SpriteComponent::getPath() const
{
  return _path;
}

void				SpriteComponent::setPath(const std::string &path)
{
  _path = path;
}
