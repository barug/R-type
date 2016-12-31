
#include "PlayerInputComponent.hpp"

const std::string PlayerInputComponent::name = "PlayerInputComponent";

PlayerInputComponent::PlayerInputComponent()
{}

const std::string		PlayerInputComponent::getName()
{
  return PlayerInputComponent::name;
}

const std::chrono::time_point<std::chrono::system_clock> &PlayerInputComponent::getLastFire() const
{
  return _lastFire;
}

void	PlayerInputComponent::setLastFire(const std::chrono::time_point<std::chrono::system_clock> &lastFire)
{
  _lastFire = lastFire;
}
