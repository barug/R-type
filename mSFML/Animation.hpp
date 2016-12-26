//
// mSFML
//

#ifndef __ANIMATION_HPP__
#define __ANIMATION_HPP__

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

class			Animation
{
public:
    Animation();

  void			addFrame(const unsigned int x1,
                                 const unsigned int x2,
                                 const unsigned int x3,
                                 const unsigned int x4);
  void			setSpriteSheet(const sf::Texture &texture);
  const sf::Texture	*getSpriteSheet() const;
  std::size_t		getSize() const;
  const sf::IntRect	&getFrame(std::size_t n) const;

private:
    std::vector<sf::IntRect>	_frames;
    const sf::Texture		*_texture;
};

#endif // __ANIMATION_HPP__
