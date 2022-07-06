#include "Scene.h"
#include "Components.h"

Sparky::Scene::Scene()
{
	
}

Sparky::Scene::~Scene()
{
}

entt::entity Sparky::Scene::CreateEntity()
{
	return m_Registry.create();
}

void Sparky::Scene::Update(Timestep ts)
{
}