#include <fstream>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Sparky.h"

const Sparky::vec2 Sparky::Window::MAX_WINDOW_SIZE = vec2(1920, 1080);

Sparky::b8 Sparky::Window::s_ShowAboutPanel = false;
Sparky::b8 Sparky::Window::s_ShowContentBrowserPanel = false;
Sparky::b8 Sparky::Window::s_ShowKeyboardShortcutsPanel = false;
Sparky::b8 Sparky::Window::s_ShowSettingsPanel = false;
Sparky::b8 Sparky::Window::s_ShowStatsPanel = false;
Sparky::b8 Sparky::Window::s_ShowTextEditorPanel = false;

Sparky::b8 Sparky::Window::s_ShowConsolePanel = true;
Sparky::b8 Sparky::Window::s_ShowInspectorPanel = true;
Sparky::b8 Sparky::Window::s_ShowSceneHierarchyPanel = true;
Sparky::b8 Sparky::Window::s_ShowScenePanel = true;

Sparky::stl::Array<Sparky::b8, GLFW_KEY_LAST> Sparky::Window::s_Keys;
Sparky::stl::Array<Sparky::b8, GLFW_KEY_LAST> Sparky::Window::s_KeysChanged;

ImFont* Sparky::Window::s_FontArial;

Sparky::Window::Window(const WindowCreateInfo* createInfo)
	:
	m_WindowSize(createInfo->windowSize),
	m_Title(createInfo->pApplicationName),
	m_Fullscreen(createInfo->fullscreen),
	m_DebugMode(createInfo->debugMode),
	m_ListExtensions(createInfo->listGPUExtensions),
	m_GLCoreProfile(createInfo->coreProfile),
	m_VSYNC(createInfo->VSYNC),
	m_GLContextVersion(createInfo->glContextVersion),
	m_ViewportFocused(true),
	m_Window(SP_NULL_HANDLE) { }

Sparky::Window::~Window() noexcept
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Sparky::Window::SetIcon(const i8* filename) const noexcept
{
	i32 width, height, nrChannels;
	u8* textureData = stbi_load(filename, &width, &height, &nrChannels, STBI_rgb_alpha);

	GLFWimage image{};
	image.width = width;
	image.height = height;
	image.pixels = textureData;
	glfwSetWindowIcon(m_Window, 1, &image);
	stbi_image_free(textureData);
}

Sparky::Window* Sparky::Window::CreateInstance(const WindowCreateInfo* createInfo)
{
	static Window* window = new Window(createInfo);

	if (window != SP_NULL_HANDLE)
		return window;
	else
		throw SparkyException(__LINE__, __FILE__);
}

Sparky::b8 Sparky::Window::Init() const
{
	glfwInit();

	i32 profileVersion = m_GLCoreProfile ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_GLContextVersion.major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_GLContextVersion.minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, profileVersion);

	m_Window = glfwCreateWindow(m_WindowSize.x, m_WindowSize.y, m_Title, SP_NULL_HANDLE, SP_NULL_HANDLE);

	if (!m_Window)
	{
		throw SparkyException(__LINE__, __FILE__);
		return false;
	}

	glfwMakeContextCurrent(m_Window);
	glfwSetFramebufferSizeCallback(m_Window, FrameBufferResizeCallback);
	glfwSetKeyCallback(m_Window, KeyPressedCallback);
	glfwSetWindowUserPointer(m_Window, (void*)this);

	m_Fullscreen ? glfwSetWindowPos(m_Window, SP_NULL, 30) : glfwSetWindowPos(m_Window, m_WindowSize.x / 4, m_WindowSize.y / 4);
	glfwSetWindowSizeLimits(m_Window, m_WindowSize.x, m_WindowSize.y, MAX_WINDOW_SIZE.x, MAX_WINDOW_SIZE.y);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw SparkyException(__LINE__, __FILE__);
		return false;
	}

	if (m_DebugMode)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(DebugCallback, SP_NULL_HANDLE);

		glDebugMessageControl(
			GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, SP_NULL, SP_NULL, false
		);

		glDebugMessageControl(
			GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_ERROR, GL_DONT_CARE, SP_NULL, SP_NULL, true
		);
		
		SP_TRACE(std::format("Graphics Card: {0}", (const i8*)glGetString(GL_RENDERER)).c_str());
		SP_TRACE(std::format("OpenGL Vendor: {0}", (const i8*)glGetString(GL_VENDOR)).c_str());
		SP_TRACE(std::format("OpenGL Version: {0}", (const i8*)glGetString(GL_VERSION)).c_str());
		SP_TRACE(std::format("GLSL Version: {0}", (const i8*)glGetString(GL_SHADING_LANGUAGE_VERSION)).c_str());
	}

	glViewport(SP_NULL, SP_NULL, m_WindowSize.x, m_WindowSize.y);

	/// ImGui Initialization
	std::string openGLVersion = std::format(
		"#version {0}{1}{2}", m_GLContextVersion.major, m_GLContextVersion.minor, m_GLContextVersion.patch
	);

	const f32 fontSize = 16.0f;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	s_FontArial =  io.Fonts->AddFontFromFileTTF("Assets/Fonts/Arial.ttf", fontSize);
	io.FontDefault = io.Fonts->AddFontFromFileTTF("Assets/Fonts/Roboto/Roboto-Regular.ttf", fontSize);
	io.Fonts->Build();
	io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports | ImGuiBackendFlags_RendererHasViewports;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
	io.WantCaptureKeyboard = true;
	io.WantCaptureMouse = true;
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init(openGLVersion.c_str());

	Editor::StyleColorsSparkyGray();

	return QueryExtensionSupport();
}

void Sparky::Window::RenderViewportPanels(FrameBuffer& framebuffer, u32 frameCount, const RendererStatistics& stats) noexcept
{
	if (s_ShowAboutPanel)              Editor::RenderAboutPanel(s_ShowAboutPanel);
	if (s_ShowConsolePanel)            Editor::RenderConsolePanel(s_ShowConsolePanel);
	if (s_ShowContentBrowserPanel)     Editor::RenderContentBrowserPanel(s_ShowContentBrowserPanel, m_Fullscreen, s_FontArial, m_Window);
	if (s_ShowInspectorPanel)          Editor::RenderInspectorPanel(s_ShowInspectorPanel);
	if (s_ShowKeyboardShortcutsPanel)  Editor::RenderKeyboardShortcutsPanel(s_ShowKeyboardShortcutsPanel);
	if (s_ShowSceneHierarchyPanel)     Editor::RenderSceneHierarchyPanel(s_ShowSceneHierarchyPanel);
	if (s_ShowScenePanel)              Editor::RenderScenePanel(m_SceneViewInfo, framebuffer);
	if (s_ShowSettingsPanel)           Editor::RenderSettingsPanel(s_ShowSettingsPanel, m_VSYNC, m_DebugMode);
	if (s_ShowStatsPanel)              Editor::RenderStatsPanel(s_ShowStatsPanel, m_VSYNC, m_GLCoreProfile, stats, frameCount, m_GLContextVersion);
	if (s_ShowTextEditorPanel)         Editor::RenderTextEditorPanel(s_ShowTextEditorPanel);
}

void Sparky::Window::CreateEditorGUIFrame(FrameBuffer& framebuffer, u32 frameCount, const RendererStatistics& stats) noexcept
{
	using namespace ImGui;

	GetStyle().WindowRounding = 5;
	GetStyle().WindowTitleAlign = { 0, 0.5 };
	GetStyle().WindowMinSize = ImVec2{ 300, 270 };
	GetStyle().TabBorderSize = 2;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	NewFrame();

	DockSpaceOverViewport(GetWindowViewport());

	Editor::RenderMainMenuBar(m_MainMenuInfo);

	RenderViewportPanels(framebuffer, frameCount, stats);

	EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());

	i32 display_w, display_h;
	glfwGetFramebufferSize(m_Window, &display_w, &display_h);
	glViewport(SP_NULL, SP_NULL, display_w, display_h);
	m_VSYNC ? glfwSwapInterval(1) : glfwSwapInterval(0);
	m_DebugMode ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		UpdatePlatformWindows();
		RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

void TextCentered(const std::string& text)
{
	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::Text(text.c_str());
}

void Sparky::Window::ToggleFullScreen() noexcept
{
	static b8 fullscreen{ m_Fullscreen };
	fullscreen = !fullscreen;

	m_Fullscreen = fullscreen;

	m_Fullscreen ? glfwMaximizeWindow(m_Window) : glfwRestoreWindow(m_Window);
}

void Sparky::Window::ProcessInput(mat4& model, f32 speed, f32& mixValue, Shader& shader) noexcept
{
	glfwPollEvents();

	if (KeyDown(GLFW_KEY_ESCAPE))  Close();
	if (KeyDown(GLFW_KEY_F1))      m_DebugMode = !m_DebugMode;
	if (KeyDown(GLFW_KEY_F2))      Editor::StyleColorsSparkyGray();
	if (KeyDown(GLFW_KEY_F3))      Editor::StyleColorsLightGray();
	if (KeyDown(GLFW_KEY_F4))      ImGui::StyleColorsDark();
	if (KeyDown(GLFW_KEY_F5))      { }
	if (KeyDown(GLFW_KEY_F6))      shader.ReCompile();
	if (KeyDown(GLFW_KEY_F11))     ToggleFullScreen();

	if (KeyDown(GLFW_KEY_F12) && KeyDown(GLFW_KEY_LEFT_SHIFT))
		Editor::ToggleFullScreenSceneView(m_SceneViewInfo);
	if (KeyDown(GLFW_KEY_SPACE) && KeyDown(GLFW_KEY_LEFT_CONTROL))
		s_ShowContentBrowserPanel = !s_ShowContentBrowserPanel;

	if (m_ViewportFocused)
	{
		if (KeyHeld(GLFW_KEY_UP))
			model *= mat4::translate({ 0, speed, 0 });
		if (KeyHeld(GLFW_KEY_DOWN))
			model *= mat4::translate({ 0, -speed, 0 });
		if (KeyHeld(GLFW_KEY_LEFT))
			model *= mat4::translate({ -speed, 0, 0 });
		if (KeyHeld(GLFW_KEY_RIGHT))
			model *= mat4::translate({ speed, 0, 0 });

		if (KeyHeld(GLFW_KEY_R))
			model *= mat4::rotate(speed * 15, {0, 0, 1});
		if (KeyHeld(GLFW_KEY_T))
			model *= mat4::rotate(-speed * 15, { 0, 0, 1 });

		if (KeyDown(GLFW_KEY_HOME))
			mixValue += 0.1f;
		if (KeyDown(GLFW_KEY_END))
			mixValue -= 0.1f;

		mixValue = std::clamp(mixValue, 0.0f, 1.0f);
	}
}

Sparky::b8 Sparky::Window::Closed() const noexcept
{
	return static_cast<b8>(glfwWindowShouldClose(m_Window));
}

Sparky::b8 Sparky::Window::QueryExtensionSupport() const
{
	if (m_ListExtensions)
	{
		i32 extensionCount;
		glGetIntegerv(GL_NUM_EXTENSIONS, &extensionCount);

		if (extensionCount == SP_NULL)
		{
			throw SparkyException(__LINE__, __FILE__);
			return false;
		}

		SP_TRACE(std::format("{0} extensions supported by implementation", extensionCount));

		for (u32 i = 0; i < (u32)extensionCount; i++)
			SP_TRACE(std::format("\t\t{0}", (const i8*)glGetStringi(GL_EXTENSIONS, i)));
	}

	return true;
}


void Sparky::Window::KeyPressedCallback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods)
{
	if (action != GLFW_RELEASE) {
		if (!s_Keys[key]) s_Keys[key] = true;
	} else s_Keys[key] = false;

	s_KeysChanged[key] = action != GLFW_REPEAT;
}

void Sparky::Window::FrameBufferResizeCallback(GLFWwindow* window, i32 width, i32 height)
{
	auto appWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

	appWindow->m_WindowSize = vec2{ static_cast<f32>(width), static_cast<f32>(height) };
	appWindow->m_Fullscreen = !appWindow->m_Fullscreen;

	glViewport(SP_NULL, SP_NULL, appWindow->m_WindowSize.x, appWindow->m_WindowSize.y);
}

void GLAPIENTRY Sparky::Window::DebugCallback(
	GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, GLchar const* message, void const* user_param
) {
	auto const src_str = [source]()
	{
		switch (source)
		{
			case GL_DEBUG_SOURCE_API:              return "API";
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:    return "WINDOW SYSTEM";
			case GL_DEBUG_SOURCE_SHADER_COMPILER:  return "SHADER COMPILER";
			case GL_DEBUG_SOURCE_THIRD_PARTY:      return "THIRD PARTY";
			case GL_DEBUG_SOURCE_APPLICATION:      return "APPLICATION";
			case GL_DEBUG_SOURCE_OTHER:            return "OTHER";
		}
	}();

	auto const type_str = [type]()
	{
		switch (type)
		{
			case GL_DEBUG_TYPE_ERROR:                return "ERROR";
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:  return "DEPRECATED_BEHAVIOR";
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:   return "UNDEFINED_BEHAVIOR";
			case GL_DEBUG_TYPE_PORTABILITY:          return "PORTABILITY";
			case GL_DEBUG_TYPE_PERFORMANCE:          return "PERFORMANCE";
			case GL_DEBUG_TYPE_MARKER:               return "MARKER";
			case GL_DEBUG_TYPE_OTHER:                return "OTHER";
		}
	}();

	auto const severity_str = [severity]()
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_NOTIFICATION:  return "NOTIFICATION";
			case GL_DEBUG_SEVERITY_LOW:           return "LOW";
			case GL_DEBUG_SEVERITY_MEDIUM:        return "MEDIUM";
			case GL_DEBUG_SEVERITY_HIGH:          return "HIGH";
		}
	}();

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		SP_TRACE((std::string)src_str + (std::string)type_str + (std::string)severity_str + (std::string)message);     break;
	case GL_DEBUG_SEVERITY_LOW:
		SP_WARN((std::string)src_str + (std::string)type_str + (std::string)severity_str + (std::string)message);      break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		SP_ERROR((std::string)src_str + (std::string)type_str + (std::string)severity_str + (std::string)message);     break;
	case GL_DEBUG_SEVERITY_HIGH:
		SP_FATAL((std::string)src_str + (std::string)type_str + (std::string)severity_str + (std::string)message);  break;
	}
}