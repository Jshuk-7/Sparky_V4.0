#include <memory>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "ProjectBrowser.h"

ProjectBrowser::ProjectBrowser(Sparky::vec2 windowSize)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(windowSize.x, windowSize.y, "Sparky Project Browser", SP_NULL_HANDLE, SP_NULL_HANDLE);

	glfwMakeContextCurrent(m_Window);
	glfwSetWindowPos(m_Window, 1920 / 2 - 400, 1080 / 2 - 300);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwSwapInterval(1);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.FontDefault = io.Fonts->AddFontFromFileTTF("Assets/Fonts/OpenSans/OpenSans-Regular.ttf", 20.0f);
	io.Fonts->Build();
	io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports | ImGuiBackendFlags_RendererHasViewports;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	StyleColorsSparkyGray();
}

ProjectBrowser::~ProjectBrowser()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void ProjectBrowser::TextCentered(const std::string& text)
{
	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::Text(text.c_str());
}

void ProjectBrowser::StyleColorsSparkyGray()
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

void ProjectBrowser::Run()
{
	while (!glfwWindowShouldClose(m_Window))
	{
		glfwPollEvents();
		if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE)) glfwTerminate();

		glClear(GL_COLOR_BUFFER_BIT);
		GUINewFrame();

		using namespace ImGui;

		auto& io = GetIO();
		
		if (Begin("Project Browser", SP_NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration))
		{
			TextCentered("Welcome To Sparky Game Engine");
			for (Sparky::u32 i = 0; i < 5; i++) Spacing();
			TextCentered("Sparky is currently in development but you can test out the engine today");

			SetCursorPos({ (800 / 2) - (300 / 2), (500 / 2) + 150 });
			if (Button("Start Engine", { 300, 40 }))
			{
				End();
				Destroy();
				
				//Sparky::Application* app = Sparky::Application::MakeInstance();
				std::unique_ptr<Sparky::Application> app = std::make_unique<Sparky::Application>();
				app->Run();
				//delete app;
			}
		}
		End();

		GUIEndFrame();

		glfwSwapBuffers(m_Window);
	}
}

void ProjectBrowser::GUINewFrame()
{
	using namespace ImGui;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	NewFrame();

	DockSpaceOverViewport(GetWindowViewport());
}

void ProjectBrowser::GUIEndFrame()
{
	using namespace ImGui;

	EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());

	Sparky::i32 display_w, display_h;
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

void ProjectBrowser::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}
