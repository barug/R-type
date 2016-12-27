# include       "SpriteComponent.hpp"

SpriteComponent::SpriteComponent(const std::string &path) : _path(path)
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
