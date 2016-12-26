//
// mSFML
//

#ifndef			__TEXTUREMANAGER_HPP__
# define		__TEXTUREMANAGER_HPP__

# include	        <unordered_map>
# include		<memory>
# include		<SFML/Graphics.hpp>

class			TextureManager
{

public:

  TextureManager();
  ~TextureManager();
  const sf::Texture  	*load(const std::string &path);

private:

  std::unordered_map<std::string,
		     std::unique_ptr<sf::Texture>>		_textures;

};

#endif			/* __TEXTUREMANAGER_HPP__  */
