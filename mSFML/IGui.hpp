//
// mSFML
//

#ifndef			__IGUI__HPP__
# define		__IGUI__HPP__

# define		DEFAULT_WINDOW_X (800)
# define		DEFAULT_WINDOW_Y (600)
# define		DEFAULT_WINDOW_NAME ("This is a mSFML demo")

# include		<string>
# include		<vector>
# include               "AnimatedSprite.hpp"

class		IGui
{

public:

    enum Key : unsigned int
    {
      NONE = 0,
      ENTER,
      TAB,
      SPACE,
      RIGHT,
      LEFT,
      DOWN,
      UP,
      K_1,
      K_2,
      K_3,
      K_4,
      K_5,
      K_6,
      K_7,
      K_8,
      K_9,
      K_0,
      K_Z,
      K_Q,
      K_S,
      K_D,
      K_W
    };

  static const int 	offsetX = 30;
  static const int	offsetY = 30;
  static const int	offsetMapX = 230;
  static const int	offsetMapY = 20;
  static const int	mapSize = 19;

  /*
  ** Dtor
  */
  virtual               ~IGui() {}

  /** Public Member Functions **/

  /*
  ** Windows methods
  */
  virtual void		update(void) = 0;
  virtual void		display(void) = 0;
  virtual void		clear(void) = 0;
  virtual bool		isAlive(void) = 0;
  virtual std::string   getCurrentInputBuffer(void) const = 0;
  virtual void          setCurrentInputBuffer(const std::string &newBuffer) = 0;

  /*
  ** Keyboard Events methods
  */
  virtual IGui::Key 	getKey(void) const = 0;
  virtual IGui::Key     getKeyRelease(void) const = 0;
  virtual void	       	handleEvents(void) = 0;

  /*
  ** Mouse Event
  */
  virtual unsigned int	getMouseX(void) const = 0;
  virtual unsigned int	getMouseY(void) const = 0;
  virtual bool		buttonLeftIsClicked(void) const = 0;
  virtual bool		buttonRightIsClicked(void) const = 0;

  /*
  ** Font methods
  */
  virtual void		loadFont(const std::string &path) = 0;
  virtual void	        writeAt(const std::string  &msg,
				const float x, const float y,
				const unsigned int hexaColorCode = 0x000000,
				const float scale = 1.) = 0;

  /*
  ** Animated Sprites
  */
  virtual Animation     loadAnimation(const std::string &path) = 0;
  virtual Animation     addFrames(const std::string &path,
                                  const unsigned int nbFrame,
                                  std::vector<unsigned int> rec) = 0;
  virtual Animation     addFrames(const std::string &path,
                                  std::vector<std::vector<unsigned int> > fullFrames) = 0;
  virtual void          addFrames(Animation &animation,
                                  const unsigned int nbFrame,
                                  const unsigned int x1,
                                  const unsigned int x2,
                                  const unsigned int x3,
                                  const unsigned int x4) = 0;
  virtual void          addFrame(Animation &animation,
                                 const unsigned int x1,
                                 const unsigned int x2,
                                 const unsigned int x3,
                                 const unsigned int x4) = 0;
  virtual void          addFrames(Animation &animation,
                                  const unsigned int nbFrame,
                                  std::vector<unsigned int> rec) = 0;
  virtual void          updateAnimatedSprite(Animation &currentAnimation,
                                             AnimatedSprite &animatedSprite,
                                             const float x,
                                             const float y) = 0;
  virtual void          updateAnimatedSprite(AnimatedSprite &animatedSprite,
                                             const float x, const float y) = 0;
  virtual void          moveAnimatedSprite(AnimatedSprite &animatedSprite,
                                           const float x, const float y) = 0;

  /*
  ** Texture methods
  */
  virtual void	        setTextureAt(const std::string &path,
				     const float x, const float y,
				     const float scale = 1.) = 0;
  virtual void	        setTextureRecAt(const std::string &path,
                                        const float x, const float y,
                                        const float h1, const float w1,
                                        const float h2, const float w2,
                                        const float scale = 1.) = 0;
  virtual void	        fillRec(const unsigned int x,
				const unsigned int y,
				const unsigned int i,
				const unsigned int j,
				const unsigned int hexaColorCode = 0x000000,
				const unsigned int alpha = 255) = 0;
  virtual void	        fillCircle(const unsigned int x,
				   const unsigned int y,
				   const unsigned int i,
				   const unsigned int j,
				   const unsigned int hexaColorCode = 0x000000) = 0;
  virtual bool	        magnetTile(const unsigned int mouseX,
				   const unsigned int mouseY,
				   const unsigned int x,
				   const unsigned int y,
				   const unsigned int intensityX = 13,
				   const unsigned int intensityY = 13) const = 0;


  /*
  ** Color converter
  */
  inline const std::vector<unsigned int> hexaToRgb(const unsigned int hexcode)
  {
    const std::vector<unsigned int> rgb =
      {
	(hexcode >> 16) & 0xFF,
	(hexcode >> 8) & 0xFF,
	(hexcode & 0xFF)
      };
    return (rgb);
  }

  inline unsigned int			rgbToHexa(const unsigned int r,
						  const unsigned int g,
						  const unsigned int b)
  {
    return ((r << 16) + (g << 8) + b);
  }

};

#endif			/* __IWINDOW__HPP__ */
