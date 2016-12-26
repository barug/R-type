//
// mSFML
//

#include <cstdio>
#include <iostream>
#include "TextureManager.hpp"

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {}

const sf::Texture			*TextureManager::load(const std::string &path)
{
  if (_textures[path].get() != NULL)
    return (_textures[path].get());
  sf::Texture			*tmp = new sf::Texture;

  if (!tmp->loadFromFile(path))
    return (NULL);
  _textures[path] = std::move(std::unique_ptr<sf::Texture>(tmp));
  return (_textures[path].get());
}
