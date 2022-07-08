#include <filesystem>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Sparky.h"

/// Once we have projects change this
static const std::filesystem::path ASSET_PATH = "Assets";

const Sparky::vec2 Sparky::Window::MAX_WINDOW_SIZE = vec2(1920, 1080);

Sparky::b8 Sparky::Window::s_ShowKeyboardShortcutsPanel = SP_FALSE;
Sparky::b8 Sparky::Window::s_ShowAboutPanel = SP_FALSE;
Sparky::b8 Sparky::Window::s_ShowSettingsPanel = SP_FALSE;
Sparky::b8 Sparky::Window::s_ShowStatsPanel = SP_FALSE;
Sparky::b8 Sparky::Window::s_ShowContentBrowserPanel = SP_FALSE;

Sparky::b8 Sparky::Window::s_ShowSceneHierarchyPanel = SP_TRUE;
Sparky::b8 Sparky::Window::s_ShowInspectorPanel = SP_TRUE;
Sparky::b8 Sparky::Window::s_ShowConsolePanel = SP_TRUE;
Sparky::b8 Sparky::Window::s_ShowScenePanel = SP_TRUE;

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
	m_ViewportFocused(SP_TRUE),
	m_Window(SP_NULL_HANDLE) { }

Sparky::Window::~Window() noexcept
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_Window);
	glfwTerminate();
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
		return SP_FALSE;
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
		return SP_FALSE;
	}

	if (m_DebugMode)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(DebugCallback, SP_NULL_HANDLE);

		glDebugMessageControl(
			GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, SP_NULL, SP_NULL, SP_FALSE
		);

		glDebugMessageControl(
			GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_ERROR, GL_DONT_CARE, SP_NULL, SP_NULL, SP_TRUE
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
	//io.FontDefault = io.Fonts->AddFontFromFileTTF("Assets/Fonts/OpenSans/OpenSans-Regular.ttf", fontSize);
	io.FontDefault = io.Fonts->AddFontFromFileTTF("Assets/Fonts/Roboto/Roboto-Regular.ttf", fontSize);
	io.Fonts->Build();
	io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports | ImGuiBackendFlags_RendererHasViewports;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
	io.WantCaptureKeyboard = SP_TRUE;
	io.WantCaptureMouse = SP_TRUE;
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init(openGLVersion.c_str());

	StyleColorsSparkyGray();

	return QueryExtensionSupport();
}

void Sparky::Window::CreateEditorGUIFrame(FrameBuffer& framebuffer, u32 frameCount, const RendererStatistics& stats) noexcept
{
	m_VSYNC ? glfwSwapInterval(1) : glfwSwapInterval(0);
	m_DebugMode ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	using namespace ImGui;

	GetStyle().WindowRounding = 5;
	GetStyle().WindowTitleAlign = { 0, 0.5 };
	GetStyle().WindowMinSize = ImVec2{ 300, 270 };
	GetStyle().TabBorderSize = 2;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	NewFrame();

	DockSpaceOverViewport(GetWindowViewport());
	RenderMainMenuBar();

	if (s_ShowKeyboardShortcutsPanel)  RenderKeyboardShortcutsPanel();
	if (s_ShowAboutPanel)              RenderAboutPanel();
	if (s_ShowSettingsPanel)           RenderSettingsPanel();
	if (s_ShowSceneHierarchyPanel)     RenderSceneHierarchyPanel();
	if (s_ShowInspectorPanel)          RenderInspectorPanel();
	if (s_ShowConsolePanel)            RenderConsolePanel();
	if (s_ShowContentBrowserPanel)     RenderContentBrowserPanel();
	if (s_ShowScenePanel)              RenderScenePanel(framebuffer);
	if (s_ShowStatsPanel)              RenderStatsPanel(stats, frameCount);

	EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());

	i32 display_w, display_h;
	glfwGetFramebufferSize(m_Window, &display_w, &display_h);
	glViewport(SP_NULL, SP_NULL, display_w, display_h);

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

void Sparky::Window::ToggleFullScreen() const noexcept
{
	static b8 fullscreen{ m_Fullscreen };
	fullscreen = !fullscreen;

	fullscreen ? glfwMaximizeWindow(m_Window) : glfwRestoreWindow(m_Window);
}

void Sparky::Window::ToggleFullScreenSceneView() noexcept
{
	static b8 fullscreenSceneView{};
	fullscreenSceneView = !fullscreenSceneView;

	if (fullscreenSceneView)
	{
		s_ShowScenePanel = SP_TRUE;

		s_ShowKeyboardShortcutsPanel = SP_FALSE;
		s_ShowAboutPanel = SP_FALSE;
		s_ShowSettingsPanel = SP_FALSE;
		s_ShowSceneHierarchyPanel = SP_FALSE;
		s_ShowInspectorPanel = SP_FALSE;
		s_ShowConsolePanel = SP_FALSE;
		s_ShowContentBrowserPanel = SP_FALSE;
		s_ShowStatsPanel = SP_FALSE;
	}
	else
	{
		s_ShowSceneHierarchyPanel = SP_TRUE;
		s_ShowInspectorPanel = SP_TRUE;
		s_ShowConsolePanel = SP_TRUE;
		s_ShowScenePanel = SP_TRUE;
	}
}

void Sparky::Window::ProcessInput(mat4& model, f32 speed, Shader& shader) noexcept
{
	glfwPollEvents();

	if (KeyDown(GLFW_KEY_ESCAPE)) Close();
	if (KeyDown(GLFW_KEY_F1))     m_DebugMode = !m_DebugMode;
	if (KeyDown(GLFW_KEY_F2))     StyleColorsSparkyGray();
	if (KeyDown(GLFW_KEY_F3))     StyleColorsLightGray();
	if (KeyDown(GLFW_KEY_F4))     ImGui::StyleColorsDark();
	if (KeyDown(GLFW_KEY_F5))     { }
	if (KeyDown(GLFW_KEY_F6))     shader.ReCompile();
	if (KeyDown(GLFW_KEY_F11))    ToggleFullScreen();

	if (KeyDown(GLFW_KEY_F12) && KeyDown(GLFW_KEY_LEFT_SHIFT))
		ToggleFullScreenSceneView();
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
			return SP_FALSE;
		}

		SP_TRACE(std::format("{0} extensions supported by implementation", extensionCount));

		for (u32 i = 0; i < (u32)extensionCount; i++)
			SP_TRACE(std::format("\t\t{0}", (const i8*)glGetStringi(GL_EXTENSIONS, i)));
	}

	return SP_TRUE;
}

void Sparky::Window::RenderMainMenuBar() const noexcept
{
	using namespace ImGui;

	if (BeginMainMenuBar())
	{
		if (BeginMenu("File"))
		{
			if (MenuItem("New", "Ctrl+N")) { }
			if (MenuItem("Open", "Ctrl+O")) { }
			if (MenuItem("Save As...", "Ctrl+Shift+S")) { }
			if (MenuItem("Settings")) s_ShowSettingsPanel = !s_ShowSettingsPanel;
			if (MenuItem("Exit")) Close();

			EndMenu();
		}

		if (BeginMenu("Edit"))
		{
			if (MenuItem("Undo", "Ctrl+Z")) {}
			if (MenuItem("Redo", "Ctrl+Shift+Z")) {}

			EndMenu();
		}

		if (BeginMenu("Window"))
		{
			if (MenuItem("Scene"))            s_ShowScenePanel = !s_ShowScenePanel;
			if (MenuItem("Scene Hierarchy"))  s_ShowSceneHierarchyPanel = !s_ShowSceneHierarchyPanel;
			if (MenuItem("Console"))          s_ShowConsolePanel = !s_ShowConsolePanel;
			if (MenuItem("Content Browser"))  s_ShowContentBrowserPanel = !s_ShowContentBrowserPanel;
			if (MenuItem("Inspector"))        s_ShowInspectorPanel = !s_ShowInspectorPanel;

			EndMenu();
		}

		if (BeginMenu("Help"))
		{
			if (MenuItem("Keyboard Shortcuts")) s_ShowKeyboardShortcutsPanel = !s_ShowKeyboardShortcutsPanel;
			if (MenuItem("About Sparky")) s_ShowAboutPanel = !s_ShowAboutPanel;

			EndMenu();
		}

		TextCentered(Log::GetCurrentTime());

		EndMainMenuBar();
	}
}

void Sparky::Window::RenderKeyboardShortcutsPanel() const noexcept
{
	using namespace ImGui;

	SetNextWindowSizeConstraints({ 600, 400 }, { 800, 600 });
	if (Begin("Keyboard Shortcuts", &s_ShowKeyboardShortcutsPanel, ImGuiWindowFlags_NoCollapse))
	{
		BeginChild("Keyboard");

		Bullet(); Text("Maximize Scene: Ctrl+Space");


		EndChild();
	}

	End();
}

void Sparky::Window::RenderAboutPanel() const noexcept
{
	using namespace ImGui;

	SetNextWindowSize({ 500, 350 });
	if (Begin("About Sparky", &s_ShowAboutPanel, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
	{
		BeginChild("About");

		TextCentered("Welcome to Sparky Game Engine.");
		TextCentered("Sparky is currently under development");

		EndChild();
	}

	End();
}

void Sparky::Window::StyleColorsLightGray() const noexcept
{
	ImVec4* colors                       = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text]                = ImVec4(1, 1, 1, 1);
	colors[ImGuiCol_WindowBg]            = ImVec4(.2, .2, .2, .95);
	colors[ImGuiCol_PopupBg]             = ImVec4(.15, .15, .15, 1);
	colors[ImGuiCol_Button]             = ImVec4(.2, .4, .75, .65);
	colors[ImGuiCol_TitleBg]             = ImVec4(.1, .1, .1, 1);
	colors[ImGuiCol_TitleBgActive]       = ImVec4(.15, .15, .15, 1);
	colors[ImGuiCol_Tab]                 = ImVec4(.2, .4, .75, .5);
	colors[ImGuiCol_TabActive]           = ImVec4(.2, .4, .75, 1);
	colors[ImGuiCol_TabUnfocusedActive]  = ImVec4(.2, .4, .75, .65);
	colors[ImGuiCol_FrameBg]             = ImVec4(.5, .5, .5, .25);
	colors[ImGuiCol_MenuBarBg]           = ImVec4(.15, .15, .15, 1);
}

void Sparky::Window::StyleColorsSparkyGray() const noexcept
{
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
	colors[ImGuiCol_WindowBg] = ImVec4(.1, .105, .11, .90);
	colors[ImGuiCol_MenuBarBg] = ImVec4(.15, .15, .15, 1);

	colors[ImGuiCol_Header] = ImVec4(.2, .205, .21, 1);
	colors[ImGuiCol_HeaderHovered] = ImVec4(.3, .305, .31, 1);
	colors[ImGuiCol_HeaderActive] = ImVec4(.15, .1505, .151, 1);

	colors[ImGuiCol_Button] = ImVec4(.2, .205, .21, 1);
	colors[ImGuiCol_ButtonHovered] = ImVec4(.3, .305, .31, 1);
	colors[ImGuiCol_ButtonActive] = ImVec4(.15, .1505, .151, 1);

	colors[ImGuiCol_FrameBg] = ImVec4(.2, .205, .21, 1);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(.3, .305, .31, 1);
	colors[ImGuiCol_FrameBgActive] = ImVec4(.15, .1505, .151, 1);

	colors[ImGuiCol_Tab] = ImVec4(.15, .1505, .151, 1);
	colors[ImGuiCol_TabHovered] = ImVec4(.38, .3805, .381, 1);
	colors[ImGuiCol_TabActive] = ImVec4(.28, .2805, .281, 1);
	colors[ImGuiCol_TabUnfocused] = ImVec4(.15, .1505, .151, 1);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(.2, .205, .21, 1);

	colors[ImGuiCol_PopupBg] = ImVec4(.15, .15, .15, 1);

	colors[ImGuiCol_TitleBg] = ImVec4(.15, .1505, .151, 1);
	colors[ImGuiCol_TitleBgActive] = ImVec4(.15, .1505, .151, 1);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(.15, .1505, .151, 1);
}

void Sparky::Window::RenderSettingsPanel() noexcept
{
	using namespace ImGui;

	SetNextWindowSizeConstraints({ 600, 400 }, { 800, 600 });
	if (Begin("Settings", &s_ShowSettingsPanel, ImGuiWindowFlags_NoCollapse))
	{
		for (u32 i = 0; i < 2; i++) Spacing();

		if (BeginChild("Settings"))
		{
			TextCentered("Editor"); Separator(); Spacing();
			if (BeginMenu("Theme"))
			{
				if (MenuItem("Sparky Gray")) StyleColorsSparkyGray();
				if (MenuItem("Light Gray")) StyleColorsLightGray();
				if (MenuItem("Original Dark")) StyleColorsDark();
				if (MenuItem("Retro Classic")) StyleColorsClassic();
				if (MenuItem("Light")) StyleColorsLight();

				ImGui::EndMenu();
			}

			for (u32 i = 0; i < 8; i++) Spacing();

			TextCentered("Graphics"); Separator(); Spacing();
			Checkbox("VSYNC", &m_VSYNC);
			Checkbox("Debug Mode", &m_DebugMode);

			EndChild();
		}
	}

	End();
}

void Sparky::Window::RenderSceneHierarchyPanel() const noexcept
{
	using namespace ImGui;

	static ImGuiDir_ dir{ ImGuiDir_Right };

	if (Begin("Scene Hierarchy", &s_ShowSceneHierarchyPanel, ImGuiWindowFlags_NoCollapse))
	{
		BeginChild("Scene Hierarchy");
		if (ArrowButton("Hello", dir))
		{
			if (dir == ImGuiDir_Down) dir = ImGuiDir_Right;
			else if (dir == ImGuiDir_Right) dir = ImGuiDir_Down;
		}

		EndChild();
	}

	End();
}

void Sparky::Window::RenderInspectorPanel() const noexcept
{
	using namespace ImGui;

	f32 pos[3]{};
	f32 rot[3]{};
	f32 scale[3]{};
	i8 name[30]{};

	if (Begin("Inspector", &s_ShowInspectorPanel, ImGuiWindowFlags_NoCollapse))
	{
		BeginChild("Inspector");

		InputText("Name", name, 30);
		Spacing();

		Text("Transform");
		SliderFloat3("Position", pos, -10, 10, "%.2f");
		SliderFloat3("Rotation", rot, -10, 10, "%.2f");
		SliderFloat3("Scale", scale, -10, 10, "%.2f");
		Spacing();
		Separator();
		Text("Box Collider");
		SliderFloat3("Center", pos, -10, 10, "%.2f");

		EndChild();
	}

	End();
}

void Sparky::Window::RenderConsolePanel() const noexcept
{
	using namespace ImGui;

	auto logs = Log::GetLogs();

	if (Begin("Console", &s_ShowConsolePanel, ImGuiWindowFlags_NoCollapse))
	{
		BeginChild("Console");

		auto logs = Log::GetLogs();

		if (!logs.empty())
		{
			for (const auto& log : logs)
			{
				Text(Log::s_LogBaseMessage); SameLine(); Text(log.c_str());
			}
		}

		EndChild();
	}

	End();
}

void Sparky::Window::RenderContentBrowserPanel() const noexcept
{
	using namespace ImGui;

	static std::filesystem::path currentDirectory = ASSET_PATH;

	i32 w, h, x, y;
	glfwGetWindowSize(m_Window, &w, &h);
	glfwGetWindowPos(m_Window, &x, &y);

	if (!m_Fullscreen)
	{
		SetNextWindowSize({ (f32)w, 375 });
		SetNextWindowPos({ (f32)x, (f32)h - 50});
	}

	if (Begin("Content Browser", &s_ShowContentBrowserPanel,
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
	{
		PushFont(s_FontArial);
		BeginChild("Browser");

		if (currentDirectory != std::filesystem::path(ASSET_PATH))
		{
			if (Button("<--"))
				currentDirectory = currentDirectory.parent_path();
		}

		for (auto& directoryEntry : std::filesystem::directory_iterator(currentDirectory))
		{
			const auto& path = directoryEntry.path();
			auto relativePath = std::filesystem::relative(path, ASSET_PATH);
			std::string filenameString = relativePath.filename().string();

			if (directoryEntry.is_directory())
			{
				if (Button(filenameString.c_str()))
					currentDirectory /= path.filename();
			}
			else
			{
				if (Button(filenameString.c_str()))
				{

				}
			}
		}

		EndChild();
		PopFont();
	}

	End();
}

void Sparky::Window::RenderScenePanel(FrameBuffer& framebuffer) noexcept
{
	using namespace ImGui;

	SetNextWindowSizeConstraints({ MAX_WINDOW_SIZE.x / 3, MAX_WINDOW_SIZE.y / 3 }, { MAX_WINDOW_SIZE.x, MAX_WINDOW_SIZE.y });
	PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	if (Begin("Scene", &s_ShowScenePanel, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar))
	{
		m_ViewportFocused = IsWindowFocused();

		if (BeginMenuBar())
		{
			if (MenuItem("Play")) { }

			if (BeginMenu("Tools"))
			{
				if (MenuItem("Stats")) s_ShowStatsPanel = !s_ShowStatsPanel;

				static b8 fullscreen{ m_Fullscreen };
				const i8* text = fullscreen ? "Minimize Scene" : "Maximize Scene";
				if (MenuItem(text))
				{
					ToggleFullScreenSceneView();
					fullscreen = !fullscreen;
				}

				EndMenu();
			}

			EndMenuBar();
		}

		BeginChild("GameRender");
		ImVec2 wsize = GetWindowSize();

		if (m_WindowSize != *((vec2*)&wsize))
		{
			framebuffer.Resize({ m_WindowSize.x, m_WindowSize.y });
			m_WindowSize = { wsize.x, wsize.y };
		}

		auto textureId = framebuffer.GetColorAttachmentId();
		Image(
			(ImTextureID)textureId,
			ImVec2{ m_WindowSize.x, m_WindowSize.y },
			ImVec2{ 0, 1 }, ImVec2{ 1, 0 }
		);

		EndChild();
	}

	PopStyleVar();

	End();
}

void Sparky::Window::RenderStatsPanel(const RendererStatistics& stats, u32 frameCount) const noexcept
{
	using namespace ImGui;

	SetNextWindowSizeConstraints({  }, { 500, 400 });
	if (Begin("Stats", &s_ShowStatsPanel, ImGuiWindowFlags_NoCollapse))
	{
		if (TreeNode("Renderer"))
		{
			TreePop();
			Indent();
			Bullet(); Text("Draw Calls: %i", stats.drawCalls);
			Bullet(); Text("Triangle Count: %i", stats.triangleCount);
			Bullet(); Text("Vertices: %i", stats.vertices);
			Unindent();
		}

		for (u32 i = 0; i < 4; i++) Spacing();

		if (TreeNode("Engine"))
		{
			TreePop();
			Indent();
			Bullet(); Text("FPS: %i", std::clamp(frameCount / (u32)glfwGetTime(), (u32)0, (u32)100000));
			Bullet(); Text(m_VSYNC ? "VSYNC: Enabled" : "VSYNC: Disabled");
			const i8* text = m_GLCoreProfile ? "OpenGL Version: %i.%i.%i core" : "OpenGL Version: %i.%i.%i";
			Bullet(); Text(text, m_GLContextVersion.major, m_GLContextVersion.minor, m_GLContextVersion.patch);
			Unindent();
		}
	}

	ImGui::End();
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