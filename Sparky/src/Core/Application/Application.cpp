#include <Windows.h>

#include "Sparky.h"

const Sparky::vec2 WINDOWED_WINDOW_SIZE{ 1280, 720 };

Sparky::Application::Application()
{
	/*PlaySound(L"Assets/Audio/HowItWas.wav", SP_NULL, SND_ASYNC);*/

	WindowCreateInfo windowInfo{};
	windowInfo.pApplicationName = "Sparky Editor";
	windowInfo.fullscreen = SP_FALSE;
	windowInfo.glContextVersion = Version(4, 6, 0);
	windowInfo.coreProfile = SP_TRUE;
	windowInfo.listGPUExtensions = SP_FALSE;
	windowInfo.debugMode = SP_TRUE;
	windowInfo.VSYNC = SP_TRUE;
	windowInfo.windowSize = windowInfo.fullscreen ? Window::MAX_WINDOW_SIZE : WINDOWED_WINDOW_SIZE;

	m_Window = Window::CreateInstance(&windowInfo);

	if (!m_Window->Init())
	{
		SP_FATAL("Failed to Initialize Window!");
		throw SparkyException(__LINE__, __FILE__);
	}

	m_ActiveScene = new Scene();
}

Sparky::Application::~Application()
{
	if (m_Window != SP_NULL_HANDLE)
		delete m_Window;
	if (m_ActiveScene != SP_NULL_HANDLE)
		delete m_ActiveScene;
}

Sparky::Application* Sparky::Application::MakeInstance()
{
	static Application* app = new Application();

	if (app != SP_NULL_HANDLE)
		return app;
	else
	{
		SP_FATAL("Failed to allocate memory for new Application!");
		throw SparkyException(__LINE__, __FILE__);
	}
}

void Sparky::Application::Run() const noexcept
{
	stl::Array<Vertex, 4> vertices{};

	              //positions                 colors                  texture coords
	vertices[0] = { vec3(-0.5f,  0.5f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f) }; // top left
	vertices[1] = { vec3( 0.5f,  0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f) }; // top right
	vertices[2] = { vec3(-0.5f, -0.5f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f) }; // bottom left
	vertices[3] = { vec3( 0.5f, -0.5f, 0.0f), vec3(1.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f) }; // bottom right

	stl::Array<u8, 6> indices{};

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	indices[3] = 1;
	indices[4] = 2;
	indices[5] = 3;

	ShaderProgramCreateInfo shaderInfo{
		"Assets/Shaders/default.vert.glsl",
		"Assets/Shaders/default.frag.glsl"
	};

	Shader shader(&shaderInfo);

	shader.SetUniform("u_Proj", mat4::orthographic(-2.75f, 2.75f));
	shader.SetUniform("u_TexImage", 0);

	mat4 model = mat4::identity();

	TextureCreateInfo texInfo{};
	texInfo.pFilename = "Assets/Textures/DarkSky.jpg";
	texInfo.format = TextureFormatType::RGBA;
	texInfo.pixelType = TexturePixelType::Smooth;
	texInfo.flipY = SP_TRUE;

	Texture texture(&texInfo);

	FrameBufferCreateInfo fbInfo{};
	fbInfo.size = Window::MAX_WINDOW_SIZE;

	FrameBuffer framebuffer(&fbInfo);
	
	u32 va, vb, ib;

	glCreateVertexArrays(1, &va);
	glCreateBuffers(1, &vb);
	glCreateBuffers(1, &ib);

	glVertexArrayVertexBuffer(va, 0, vb, SP_NULL, sizeof(Vertex));
	glNamedBufferStorage(vb, vertices.Bytes(), vertices.Data(), GL_DYNAMIC_STORAGE_BIT);

	glEnableVertexArrayAttrib(va, 0);
	glVertexArrayAttribFormat(va, 0, 3, GL_FLOAT, SP_FALSE, SP_NULL);
	glVertexArrayAttribBinding(va, 0, 0);

	glEnableVertexArrayAttrib(va, 1);
	glVertexArrayAttribFormat(va, 1, 3, GL_FLOAT, SP_FALSE, sizeof(vec3));
	glVertexArrayAttribBinding(va, 1, 0);

	glEnableVertexArrayAttrib(va, 2);
	glVertexArrayAttribFormat(va, 2, 2, GL_FLOAT, SP_FALSE, sizeof(vec3) * 2);
	glVertexArrayAttribBinding(va, 2, 0);

	glVertexArrayElementBuffer(va, ib);
	glNamedBufferStorage(ib, indices.Bytes(), indices.Data(), GL_DYNAMIC_STORAGE_BIT);

	RendererStatistics stats{};
	stats.drawCalls = 1;
	stats.triangleCount = 2;
	stats.vertices = 6;

	Renderer renderer;
	renderer.SetRenderClearColor({ .1, .1, .11 });
	renderer.SubmitRendererStats(stats);
	
	u32 frameCount{};

	while (!m_Window->Closed())
	{
		framebuffer.Bind();
		renderer.RenderClear();

		shader.SetUniform("u_Model", model);
		m_Window->ProcessInput(model, 0.05f, shader);

		texture.Bind(0);
		glBindVertexArray(va);

		renderer.Render(GL_TRIANGLES, sizeof(indices) / sizeof(u8), GL_UNSIGNED_BYTE);

		renderer.Update();
		framebuffer.Unbind();

		m_Window->CreateEditorGUIFrame(framebuffer, renderer.GetStats(), frameCount);

		frameCount++;
	}

	shader.Destroy();
}