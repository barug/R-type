//
// mSFML
//

# include "Animation.hpp"

Animation::Animation() : _texture(NULL)
{}

Animation::~Animation()
{}

void                    Animation::addFrame(const unsigned int x1,
                                            const unsigned int x2,
                                            const unsigned int x3,
                                            const unsigned int x4)
{
  _frames.push_back(sf::IntRect(x1, x2, x3, x4));
}

void                    Animation::setSpriteSheet(const sf::Texture& texture)
{
  _texture = &texture;
}

const sf::Texture       *Animation::getSpriteSheet() const
{
  return _texture;
}

std::size_t             Animation::getSize() const
{
  return _frames.size();
}

const sf::IntRect       &Animation::getFrame(std::size_t n) const
{
  return _frames[n];
}
