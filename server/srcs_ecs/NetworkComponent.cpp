#include	"IComponent.hpp"
#include	"../includes_ecs/NetworkComponent.hpp"

const std::string NetworkComponent::name = "NetworkComponent";

NetworkComponent::NetworkComponent() : _ip(),
				       _port()
{}

NetworkComponent::~NetworkComponent() {}

const std::string		NetworkComponent::getName()
{
  return name;
}
