#include <stb_image.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "ProjectBrowser.h"
#include "Core/Editor/EditorTools.h"

Sparky::ProjectBrowser::ProjectBrowser(vec2 windowSize)
	: m_WindowSize(windowSize)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, SP_FALSE);

	const i8* title{ "Sparky Game Engine v0.3.0 - Development Build (Project Browser)" };
	m_Window = glfwCreateWindow(m_WindowSize.x, m_WindowSize.y, title, SP_NULL_HANDLE, SP_NULL_HANDLE);

	glfwMakeContextCurrent(m_Window);
	glfwSetWindowPos(m_Window, Window::MAX_WINDOW_SIZE.x / 2 - 400, Window::MAX_WINDOW_SIZE.y / 2 - 300);

	i32 width, height, nrChannels;
	const i8* filename{ "Assets/Resources/SparkyLogo.jpg" };
	u8* textureData = stbi_load(filename, &width, &height, &nrChannels, STBI_rgb_alpha);

	GLFWimage image{};
	image.width = width;
	image.height = height;
	image.pixels = textureData;
	glfwSetWindowIcon(m_Window, 1, &image);
	stbi_image_free(textureData);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwSwapInterval(1);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.FontDefault = io.Fonts->AddFontFromFileTTF("Assets/Fonts/Roboto/Roboto-Regular.ttf", 16.5f);
	io.Fonts->Build();
	io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports | ImGuiBackendFlags_RendererHasViewports;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	StyleColorsSparkyGray();
}

void Sparky::ProjectBrowser::StyleColorsSparkyGray()
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

void Sparky::ProjectBrowser::Run()
{
	stl::Array<const i8*, 8> features{};
	features[0] = "Language";
	features[1] = "C++";
	features[2] = "Graphics API";
	features[3] = "OpenGL";
	features[4] = "3D?";
	features[5] = "Yes!, at some point";
	features[6] = "Game Object Managment System";
	features[7] = "ECS";

	while (!glfwWindowShouldClose(m_Window))
	{
		ProcessInput();

		GUINewFrame();

		using namespace ImGui;
		
		if (Begin("Project Browser", SP_NULL,
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration))
		{
			ImGuiStyle* style = &GetStyle();
			style->Colors[ImGuiCol_Button] = ImVec4(0.8f, 0.0f, 0.0f, 1.0f);
			style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.8f, 0.0f, 0.0f, 1.0f);
			style->Colors[ImGuiCol_ButtonHovered] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

			if (BeginMainMenuBar())
			{
				if (BeginMenu("Options"))
				{
					if (MenuItem("Exit")) SP_EXIT(SP_EXIT_SUCCESS);

					ImGui::EndMenu();
				}

				Editor::TextCentered(Log::GetCurrentTime());

				EndMainMenuBar();
			}

			for (u32 i = 0; i < 5; i++) Spacing();
			Editor::TextCentered("Welcome To Sparky Game Engine");
			for (u32 i = 0; i < 5; i++) Spacing();
			Editor::TextCentered("Sparky is currently under heavy development");
			Editor::TextCentered("But you can still beta test the engine today!");

			for (u32 i = 0; i < 5; i++) Spacing();
			if (TreeNode("Features"))
			{
				TreePop();
				Indent();
				if (BeginTable("Features Table", 2))
				{
					for (size_t i = 0; i < features.Size(); i++)
					{
						TableNextColumn();
						Text("%s", features[i]);
					}

					EndTable();
				}
				Unindent();
			}

			ImVec2 buttonSize(325, 45);
			SetCursorPos({
				(m_WindowSize.x / 2) - (buttonSize.x / 2),
				(m_WindowSize.y / 2) + 150
			});
			if (Button("Launch Editor", buttonSize))
			{
				Destroy();	
				RunGameEngine();
			}
			
			SetCursorPos({ m_WindowSize.x - 130, m_WindowSize.y - 50 });
			Text("Development Build");
		}

		GUIEndFrame();
	}
}

void Sparky::ProjectBrowser::ProcessInput()
{
	glfwPollEvents();

	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE))
		SP_EXIT(SP_EXIT_SUCCESS);
}

void Sparky::ProjectBrowser::RunGameEngine()
{
	Application* app = Application::MakeInstance();
	app->Run();

	if (app != SP_NULL_HANDLE)
		delete app;

	SP_EXIT(SP_EXIT_SUCCESS);
}

void Sparky::ProjectBrowser::GUINewFrame()
{
	using namespace ImGui;

	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	NewFrame();
}

void Sparky::ProjectBrowser::GUIEndFrame()
{
	using namespace ImGui;

	End();

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

	glfwSwapBuffers(m_Window);
}

void Sparky::ProjectBrowser::Destroy()
{
	ImGui::End();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}