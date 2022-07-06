#pragma once

#include <entt.hpp>

#include "Config/Defines.h"
#include "Core/Timestep.h"

namespace Sparky {
	class Scene
	{
	public:
		Scene();
		~Scene();

		//TEMP
		entt::registry& reg() { return m_Registry; }

		entt::entity CreateEntity();

		void Update(Timestep ts);
	private:
		entt::registry m_Registry;
	};
}