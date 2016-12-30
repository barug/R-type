
#ifndef _SCRIPT_COMPONENT_HPP_
# define _SCRIPT_COMPONENT_HPP_

# include "IComponent.hpp"
# include "IScript.hpp"

class				ScriptComponent : public IComponent
{
public:
  static const std::string	name;
  
private:

  IScript			*_script;

public:
  ScriptComponent();
  virtual const std::string	getName();
  void				setScript(IScript *script);
  void				executeScript();
};

#endif /* !_SCRIPT_COMPONENT_HPP_ */
