#pragma once

#define GLFW_INCLUDE_OPENGL
#include <GLFW/glfw3.h>

#include <imgui.h>

#include "Config/Defines.h"
#include "Math/SparkyMath.h"
#include "Core/SparkySTL/SparkySTL.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Objects/FrameBuffer/FrameBuffer.h"

namespace Sparky {

	struct WindowCreateInfo {
		const i8* pApplicationName;
		Version glContextVersion;
		b8 fullscreen;
		b8 coreProfile;
		b8 listGPUExtensions;
		b8 debugMode;
		b8 VSYNC;
		vec2 windowSize;
	};

	class Window
	{
	public:
		static Window* CreateInstance(const WindowCreateInfo* createInfo);
		b8 Init() const;

		void CreateEditorGUIFrame(FrameBuffer& framebuffer, u32 frameCount, const RendererStatistics& stats) noexcept;

		void ProcessInput(mat4& model, f32 speed, Shader& shader) noexcept;
		b8 Closed() const noexcept;
		inline void Close() const noexcept { glfwSetWindowShouldClose(m_Window, SP_TRUE); }

		inline static b8 KeyHeld(i32 key) noexcept { return s_Keys[key]; }

		inline static b8 KeyChanged(i32 key) noexcept
		{
			bool ret = s_KeysChanged[key];
			s_KeysChanged[key] = false;
			return ret;
		}

		inline static b8 KeyDown(int key) noexcept { return s_Keys[key] && KeyChanged(key); }
		inline static b8 KeyUp(int key) noexcept { return !s_Keys[key] && KeyChanged(key); }

	public:
		static const vec2 MAX_WINDOW_SIZE;

		~Window() noexcept;

	private:
		Window(const WindowCreateInfo* createInfo);
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		b8 QueryExtensionSupport() const;

		void ToggleFullScreen() const noexcept;
		void ToggleFullScreenSceneView() noexcept;

		void RenderMainMenuBar() const noexcept;
		void RenderKeyboardShortcutsPanel() const noexcept;
		void RenderAboutPanel() const noexcept;
		void StyleColorsLightGray() const noexcept;
		void StyleColorsSparkyGray() const noexcept;
		void RenderSettingsPanel() noexcept;
		void RenderSceneHierarchyPanel() const noexcept;
		void RenderInspectorPanel() const noexcept;
		void RenderConsolePanel() const noexcept;
		void RenderContentBrowserPanel() const noexcept;
		void RenderScenePanel(FrameBuffer& framebuffer) noexcept;
		void RenderStatsPanel(const RendererStatistics& stats, u32 frameCount) const noexcept;

		static void KeyPressedCallback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods);
		static void FrameBufferResizeCallback(GLFWwindow* window, i32 width, i32 height);
		static void GLAPIENTRY DebugCallback(
			GLenum source, GLenum type,
			GLuint id, GLenum severity,
			GLsizei length, GLchar const* message,
			void const* user_param
		);

	private:
		vec2 m_WindowSize;
		const i8* m_Title;

		b8 m_Fullscreen;
		b8 m_DebugMode;
		b8 m_ListExtensions;
		b8 m_GLCoreProfile;
		b8 m_VSYNC;

		Version m_GLContextVersion;

		b8 m_ViewportFocused;

		static stl::Array<b8, GLFW_KEY_LAST> s_Keys;
		static stl::Array<b8, GLFW_KEY_LAST> s_KeysChanged;

		static b8 s_ShowKeyboardShortcutsPanel;
		static b8 s_ShowAboutPanel;
		static b8 s_ShowSettingsPanel;
		static b8 s_ShowSceneHierarchyPanel;
		static b8 s_ShowInspectorPanel;
		static b8 s_ShowConsolePanel;
		static b8 s_ShowContentBrowserPanel;
		static b8 s_ShowScenePanel;
		static b8 s_ShowStatsPanel;

		static ImFont* s_FontArial;

		mutable GLFWwindow* m_Window;

	};
}