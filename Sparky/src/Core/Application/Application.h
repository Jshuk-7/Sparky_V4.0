#pragma once

#include "Core/Window/Window.h"
#include "Core/Scene/Scene.h"

namespace Sparky {
	class Application
	{
	public:
		static Application* MakeInstance();

		void Run() const noexcept;

		~Application();

	private:
		Application();
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		Window* m_Window;
		Scene* m_ActiveScene;
	};
}