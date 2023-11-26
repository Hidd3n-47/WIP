#include "pch.h"
#include "ComponentManager.h"

#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"

namespace jci {

ComponentManager::ComponentManager()
{
	//m_components[ComponentTypes::Transform] = ComponentArray<Transform>()
}

ComponentManager::~ComponentManager()
{

}

} // Namespace jci.