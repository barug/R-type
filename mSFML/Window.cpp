//
// mSFML
//

#include <iostream>
#include <ctype.h>
#include "Window.hpp"

Window::Window(const std::string &windowName,
               const int winX,
               const int winY,
               const std::string &fontPath)
  : _window(sf::VideoMode(winX, winY), windowName.c_str()),
    _frameClock(),
    _keyPress(NONE),
    _keyRelease(NONE),
    _key_map({{sf::Keyboard::Unknown,	IGui::NONE},
             {sf::Keyboard::Return,     IGui::ENTER},
             {sf::Keyboard::Tab,        IGui::TAB},
	     {sf::Keyboard::Space,	IGui::SPACE},
	     {sf::Keyboard::Right,	IGui::RIGHT},
	     {sf::Keyboard::Left,	IGui::LEFT},
	     {sf::Keyboard::Up,		IGui::UP},
	     {sf::Keyboard::Down,	IGui::DOWN},
	     {sf::Keyboard::Num0,	IGui::K_0},
	     {sf::Keyboard::Num1,	IGui::K_1},
	     {sf::Keyboard::Num2,	IGui::K_2},
	     {sf::Keyboard::Num3,	IGui::K_3},
	     {sf::Keyboard::Num4,	IGui::K_4},
	     {sf::Keyboard::Num5,	IGui::K_5},
	     {sf::Keyboard::Num6,	IGui::K_6},
	     {sf::Keyboard::Num7,	IGui::K_7},
	     {sf::Keyboard::Num8,	IGui::K_8},
             {sf::Keyboard::Num9,	IGui::K_9},
             {sf::Keyboard::Z,          IGui::K_Z},
             {sf::Keyboard::Q,          IGui::K_Q},
             {sf::Keyboard::S,          IGui::K_S},
             {sf::Keyboard::D,          IGui::K_D}})
{
  this->_window.setFramerateLimit(60);
  if (fontPath != "")
    this->loadFont(fontPath);
  std::cout << "[Window::Window] "
	    << windowName << " "
	    << winX << "x"
	    << winY
	    << std::endl;
}

Window::~Window() {}

/*
** Window
*/
void			Window::update(void)
{
  _frameTime = _frameClock.restart();
}

bool			Window::isAlive(void)
{
  return (_window.isOpen());
}

void			Window::display(void)
{
  _window.display();
}

void			Window::clear(void)
{
  _window.clear(sf::Color::Black);
}

/*
** Keyboard Event
*/

void			Window::handleEvents(void)
{
  sf::Event		event;

  while (this->_window.pollEvent(event))
    {
      switch (event.type)
	{
	case sf::Event::Closed:
	  if (DEBUG)
	    std::cout << "[Window::handleEvents] Closed window event" << std::endl;
	  this->_window.close();
	  break;
	case sf::Event::KeyPressed:
	  if (event.key.code == sf::Keyboard::Escape)
	    {
	      if (DEBUG)
		std::cout << "[Window::handleEvents] Closed window event" << std::endl;
	      this->_window.close();
	    }
	  else if (event.key.code)
            if ((this->_keyPress = this->_key_map[event.key.code]) == NONE)
              std::cout << "[key pressed] => code : [" << event.key.code << "]" << std::endl;
	  break;
	case sf::Event::KeyReleased:
	  switch (event.key.code)
	    {
	    default:
	      this->_keyPress = NONE;
              this->_keyRelease = this->_key_map[event.key.code];
	      break;
	    }
	  break;
        case sf::Event::TextEntered:
          if (event.text.unicode == 8 && !_currentBuffer.empty())
            _currentBuffer.pop_back();
          else if (isalpha(event.text.unicode) ||
                   isdigit(event.text.unicode) ||
                   event.text.unicode == '.')
            _currentBuffer.push_back(event.text.unicode);
        default:
          break;
        }
    }
}

std::string             Window::getCurrentInputBuffer(void) const
{
  std::string           buffer;

  for (auto it : _currentBuffer)
    buffer += it;
  return buffer;
}

void                    Window::setCurrentInputBuffer(const std::string &newBuffer)
{
  _currentBuffer.erase(_currentBuffer.begin(), _currentBuffer.end());
  for (auto it : newBuffer)
    _currentBuffer.push_back(it);
}

IGui::Key		Window::getKey(void) const
{
  return (this->_keyPress);
}

IGui::Key               Window::getKeyRelease(void) const
{
  return (this->_keyRelease);
}

/*
** Mouse Events
*/
unsigned int		Window::getMouseX(void) const
{
  return (this->_mouse.getPosition(this->_window).x);
}

unsigned int		Window::getMouseY(void) const
{
  return (this->_mouse.getPosition(this->_window).y);
}

bool			Window::buttonLeftIsClicked(void) const
{
  return (this->_mouse.isButtonPressed(sf::Mouse::Button::Left));
}

bool			Window::buttonRightIsClicked(void) const
{
  return (this->_mouse.isButtonPressed(sf::Mouse::Button::Right));
}

/*
** Font
*/
void			Window::loadFont(const std::string &path)
{
  this->_font.loadFromFile(path);
}

void			Window::writeAt(const std::string &msg,
                                        const float x, const float y,
                                        const unsigned int hexaColorCode,
                                        const float scale)
{
  std::vector<unsigned int> rgb = hexaToRgb(hexaColorCode);
  sf::Text text;

  text.setFont(this->_font);
  text.setString(msg);
  text.setFillColor(sf::Color(rgb[0], rgb[1], rgb[2]));
  text.setScale(scale, scale);
  text.setPosition(x, y);
  this->_window.draw(text);
}
void			Window::writeAt(const std::string &msg, const std::string &fontPath,
                                        const float x, const float y,
                                        const unsigned int hexaColorCode,
                                        const float scale)
{
  std::vector<unsigned int> rgb = hexaToRgb(hexaColorCode);
  sf::Text text;

  this->_font.loadFromFile(fontPath);
  text.setFont(this->_font);
  text.setString(msg);
  text.setFillColor(sf::Color(rgb[0], rgb[1], rgb[2]));
  text.setScale(scale, scale);
  text.setPosition(x, y);
  this->_window.draw(text);
}

/*
** Animated Sprite
*/

Animation		Window::loadAnimation(const std::string &path)
{
  Animation		animation;
  const sf::Texture	*texture;

  if ((texture = _manager.load(path)) == NULL)
    throw std::out_of_range("Failed to load texture " + path);
  animation.setSpriteSheet(*texture);
  return (animation);
}

Animation               Window::addFrames(const std::string &path,
                                          const unsigned int nbFrame,
                                          std::vector<unsigned int> rec)
{
  Animation animation = loadAnimation(path);
  if (!nbFrame)
    {
      unsigned int j = 0;
      for (unsigned int i = 0; i < rec.size(); i++)
        {
          if ((i % 4) == 0)
            {
              // animation.addFrame(j * rec[0], rec[1], rec[2], rec[3]);
              j++;
            }
        }
    }
  else
    {
      for (unsigned int i = 0; i < nbFrame; i++)
        animation.addFrame(i * rec[0], rec[1], rec[2], rec[3]);
    }
  return animation;
}

Animation               Window::addFrames(const std::string &path,
                                          std::vector<std::vector<unsigned int> > fullFrames)
{
  Animation animation = loadAnimation(path);
  for (unsigned int i = 0; i < fullFrames.size(); i++)
    {
      for (unsigned int j = 0; j < fullFrames[i].size(); j++)
        {
          animation.addFrame(fullFrames[i][0], fullFrames[i][1], fullFrames[i][2], fullFrames[i][3]);
        }
    }
  return animation;
}

void			Window::addFrames(Animation &animation,
                                          const unsigned int nbFrame,
                                          const unsigned int x1,
                                          const unsigned int x2,
                                          const unsigned int x3,
                                          const unsigned int x4)
{
  for (unsigned int i = 0; i < nbFrame; i++)
    animation.addFrame(i * x1, x2, x3, x4);
}

void			Window::addFrames(Animation &animation,
                                          const unsigned int nbFrame,
                                          std::vector<unsigned int> rec)
{
  for (unsigned int i = 0; i < nbFrame; i++)
    animation.addFrame(i * rec[0], rec[1], rec[2], rec[3]);
}

void			Window::addFrame(Animation &animation,
                                         const unsigned int x1,
                                         const unsigned int x2,
                                         const unsigned int x3,
                                         const unsigned int x4)
{
  animation.addFrame(x1, x2, x3, x4);
}

void			Window::updateAnimatedSprite(Animation &currentAnimation,
                                                     AnimatedSprite &animatedSprite,
                                                     const float x, const float y)
{
  animatedSprite.play(currentAnimation);
  animatedSprite.setPosition(x, y);
  animatedSprite.update(_frameTime);
  this->_window.draw(animatedSprite);
}

void			Window::updateAnimatedSprite(AnimatedSprite &animatedSprite,
                                                     const float x, const float y)
{
  animatedSprite.play(*animatedSprite.getAnimation());
  animatedSprite.setPosition(x, y);
  animatedSprite.update(_frameTime);
  this->_window.draw(animatedSprite);
}

void			Window::moveAnimatedSprite(AnimatedSprite &animatedSprite,
                                                   const float x, const float y)
{
  animatedSprite.move(x * _frameTime.asSeconds(), y * _frameTime.asSeconds());
}

/*
** textures
*/
void			Window::setTextureAt(const std::string &path,
                                             const float x, const float y,
                                             const float scale)
{
  sf::Sprite		sprite;
  const sf::Texture	*texture;

  if ((texture = _manager.load(path)) == NULL)
    throw std::out_of_range("Failed to load texture " + path);
  sprite.setTexture(*texture);
  sprite.setPosition(x, y);
  sprite.setScale(scale, scale);
  this->_window.draw(sprite);
}

void			Window::setTextureRecAt(const std::string &path,
                                                const float x, const float y,
                                                const float h1, const float w1,
                                                const float h2, const float w2,
                                                const float scale)
{
  sf::Sprite		sprite;
  const sf::Texture	*texture;

  if (!(texture = _manager.load(path)))
    throw std::out_of_range("Failed to load texture " + path);
  sprite.setTexture(*texture);
  sprite.setTextureRect(sf::IntRect(h1, w1, h2, w2));
  sprite.setPosition(sf::Vector2f(x, y));
  sprite.setScale(scale, scale);
  this->_window.draw(sprite);
}

/*
** Fill Rectangle
*/
void			Window::fillRec(const unsigned int x,
                                        const unsigned int y,
                                        const unsigned int i,
                                        const unsigned int j,
                                        const unsigned int hexaColorCode,
                                        const unsigned int alpha)
{
  std::vector<unsigned int> rgb = hexaToRgb(hexaColorCode);
  sf::RectangleShape rectangle;

  rectangle.setPosition(sf::Vector2f(x, y));
  rectangle.setSize(sf::Vector2f(i, j));
  rectangle.setFillColor(sf::Color(rgb[0], rgb[1], rgb[2], alpha));
  this->_window.draw(rectangle);
}

void			Window::fillCircle(const unsigned int x,
                                           const unsigned int y,
                                           const unsigned int i,
                                           const unsigned int j,
                                           const unsigned int hexaColorCode)
{
  std::vector<unsigned int> rgb = hexaToRgb(hexaColorCode);
  sf::CircleShape circle;

  circle.setPosition(x, y);
  circle.setScale(sf::Vector2f(i, j));
  circle.setFillColor(sf::Color(rgb[0], rgb[1], rgb[2], 255));
  this->_window.draw(circle);
}

bool			Window::magnetTile(const unsigned int mouseX,
                                           const unsigned int mouseY,
                                           const unsigned int x,
                                           const unsigned int y,
                                           const unsigned int intensityX,
                                           const unsigned int intensityY) const
{
  for (unsigned int i = 0; i < intensityX; i++)
    for (unsigned int j = 0; j < intensityY; j++)
      if ((mouseX + i == x && mouseY + i == y) ||
	  (mouseX + i == x && mouseY + j == y) ||
	  (mouseX + j == x && mouseY + j == y) ||
	  (mouseX + j == x && mouseY + i == y) ||

	  (mouseX + i == x && mouseY - i == y) ||
	  (mouseX + i == x && mouseY - j == y) ||
	  (mouseX + j == x && mouseY - j == y) ||
	  (mouseX + j == x && mouseY - i == y) ||

	  (mouseX - i == x && mouseY + i == y) ||
	  (mouseX - i == x && mouseY + j == y) ||
	  (mouseX - j == x && mouseY + j == y) ||
	  (mouseX - j == x && mouseY + i == y) ||

	  (mouseX - i == x && mouseY - i == y) ||
	  (mouseX - i == x && mouseY - j == y) ||
	  (mouseX - j == x && mouseY - j == y) ||
	  (mouseX - j == x && mouseY - i == y))
	return (true);
  return (false);
}
