
#include "ScriptComponent.hpp"
#include "MonsterSpawnScript.hpp"

const std::string	ScriptComponent::name = "ScriptComponent";

ScriptComponent::ScriptComponent()
{}

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
