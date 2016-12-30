//
// mSFML
//

#ifndef		__WINDOW__HPP__
# define	__WINDOW__HPP__

# include	<SFML/Window.hpp>
# include	<SFML/Graphics.hpp>
# include	<SFML/Graphics/Font.hpp>

# include	"mSFML.hpp"
# include	"IGui.hpp"
# include	"TextureManager.hpp"

class		Window : public IGui
{

public:
  // classic ctor
  Window(const std::string &name = DEFAULT_WINDOW_NAME,
	       const int windowX = DEFAULT_WINDOW_X,
	       const int windowY = DEFAULT_WINDOW_Y,
               const std::string &fontPath = "");
  // font ctor
  virtual ~Window();

  /*
  ** Windows methods
  */
  virtual void		update(void);
  virtual void		display(void);
  virtual void		clear(void);
  virtual bool		isAlive(void);
  virtual std::string   getCurrentInputBuffer(void) const;
  virtual void          setCurrentInputBuffer(const std::string &newBuffer);

  /*
  ** Keyboard Events methods
  */
  virtual IGui::Key	getKey(void) const;
  virtual IGui::Key     getKeyRelease(void) const;
  virtual void		handleEvents(void);

  /*
  ** Mouse Event
  */
  virtual unsigned int	getMouseX(void) const;
  virtual unsigned int	getMouseY(void) const;
  virtual bool	        buttonLeftIsClicked(void) const;
  virtual bool	        buttonRightIsClicked(void) const;

  /*
  ** Font methods
  */
  virtual void		loadFont(const std::string &path);
  virtual void	        writeAt(const std::string  &msg,
				const float x, const float y,
				const unsigned int hexaColorCode = 0x000000,
				const float scale = 1.);
  virtual void	        writeAt(const std::string  &msg, const std::string &fontPath,
				const float x, const float y,
				const unsigned int hexaColorCode = 0x000000,
				const float scale = 1.);

  /*
  ** Animated Sprites
  */
  virtual Animation     loadAnimation(const std::string &path);
  virtual Animation     addFrames(const std::string &path,
                                  const unsigned int nbFrame,
                                  std::vector<unsigned int> rec);
  virtual Animation     addFrames(const std::string &path,
                                  std::vector<std::vector<unsigned int> > fullFrames);
  virtual void          addFrames(Animation &animation,
                                  const unsigned int nbFrame,
                                  const unsigned int x1,
                                  const unsigned int x2,
                                  const unsigned int x3,
                                  const unsigned int x4);
  virtual void          addFrames(Animation &animation,
                                  const unsigned int nbFrame,
                                  std::vector<unsigned int> rec);
  virtual void          addFrame(Animation &animation,
                                 const unsigned int x1,
                                 const unsigned int x2,
                                 const unsigned int x3,
                                 const unsigned int x4);
  virtual void          updateAnimatedSprite(Animation &currentAnimation,
                                             AnimatedSprite &animatedSprite,
                                             const float x,
                                             const float y);
  virtual void          updateAnimatedSprite(AnimatedSprite &animatedSprite,
                                             const float x, const float y);
  virtual void          moveAnimatedSprite(AnimatedSprite &animatedSprite,
                                           const float x, const float y);

  /*
  ** Texture methods
  */
  virtual void	        setTextureAt(const std::string &path,
				     const float x, const float y,
				     const float scale = 1.);
  virtual void	        setTextureRecAt(const std::string &path,
                                        const float x, const float y,
                                        const float h1, const float w1,
                                        const float h2, const float w2,
                                        const float scale = 1.);
  virtual void	        fillRec(const unsigned int x,
				const unsigned int y,
				const unsigned int i,
				const unsigned int j,
				const unsigned int hexaColorCode = 0x000000,
				const unsigned int alpha = 255);
  virtual void	        fillCircle(const unsigned int x,
				   const unsigned int y,
				   const unsigned int i,
				   const unsigned int j,
				   const unsigned int hexaColorCode = 0x000000);
  virtual bool	        magnetTile(const unsigned int mouseX,
				   const unsigned int mouseY,
				   const unsigned int x,
				   const unsigned int y,
				   const unsigned int intensityX,
				   const unsigned int intensityY) const;

private:
  sf::RenderWindow	_window;
  sf::Font		_font;
  sf::Text		_text;
  sf::Sprite		_sprite;
  sf::Time              _frameTime;
  sf::Clock             _frameClock;
  sf::Mouse		_mouse;

  IGui::Key		_keyPress;
  IGui::Key		_keyRelease;
  std::map<sf::Keyboard::Key, IGui::Key> _key_map;

  std::vector<char>     _currentBuffer;

  TextureManager	_manager;

};

#endif		/* __WINDOW__HPP__ */
