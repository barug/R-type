
#include       "SpriteComponent.hpp"

const std::string SpriteComponent::name = "SpriteComponent";

SpriteComponent::SpriteComponent()
{}

SpriteComponent::~SpriteComponent()
{}

const std::string               SpriteComponent::getName()
{
  return SpriteComponent::name;
}

const std::string&              SpriteComponent::getPath() const
{
  return _path;
}

void				SpriteComponent::setPath(const std::string &path)
{
  _path = path;
}
