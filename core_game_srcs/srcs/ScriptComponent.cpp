
#include "ScriptComponent.hpp"

const std::string	ScriptComponent::name = "ScriptComponent";

const std::string	ScriptComponent::getName()
{
  return ScriptComponent::name;
}

void			ScriptComponent::setScript(IScript *script)
{
  _script = script;
}

void			ScriptComponent::executeScript()
{
  (*_script)();
}
