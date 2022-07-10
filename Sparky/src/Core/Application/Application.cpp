#include <Windows.h>

#include "Sparky.h"

Sparky::Application::Application()
{
	WindowCreateInfo windowInfo{};
	windowInfo.pApplicationName = "Sparky Editor";
	windowInfo.glContextVersion = Version(4, 6, 0);
	windowInfo.fullscreen = false;
	windowInfo.coreProfile = true;
	windowInfo.listGPUExtensions = false;
	windowInfo.debugMode = true;
	windowInfo.VSYNC = true;
	windowInfo.windowSize = windowInfo.fullscreen ? Window::MAX_WINDOW_SIZE : vec2(1280, 720);

	m_Window = Window::CreateInstance(&windowInfo);

	if (!m_Window->Init())
	{
		SP_FATAL("Failed to Initialize Window!");
		throw SparkyException(__LINE__, __FILE__);
	}
	m_Window->SetIcon("Assets/Resources/SparkyLogo.jpg");

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

	/// Must use a wide/multibyte string WINDOWS ONLY
	//PlaySound(L"Assets/Audio/Music", SP_NULL, SND_ASYNC);

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
	shader.SetUniform("u_TexImage2", 1);

	mat4 model = mat4::identity();

	TextureCreateInfo texInfo{};
	texInfo.pFilename = "Assets/Resources/SparkyLogo.jpg";
	texInfo.format = TextureFormatType::RGBA;
	texInfo.pixelType = TexturePixelType::Smooth;
	texInfo.flipY = true;

	TextureCreateInfo texInfo2{};
	texInfo2.pFilename = "Assets/Textures/OpenGL.png";
	//texInfo2.pFilename = "Assets/Textures/Shawn.png";
	texInfo2.format = TextureFormatType::RGBA;
	texInfo2.pixelType = TexturePixelType::Smooth;
	texInfo2.flipY = true;

	Texture texture(&texInfo);
	Texture texture2(&texInfo2);

	FrameBufferCreateInfo fbInfo{};
	fbInfo.size = Window::MAX_WINDOW_SIZE;

	FrameBuffer framebuffer(&fbInfo);

	VertexBufferCreateInfo vbInfo{};
	vbInfo.dataType = VertexBufferDataType::Float;
	vbInfo.storageType = VertexBufferStorageType::Dynamic;
	vbInfo.stride = static_cast<u32>(sizeof(Vertex));
	vbInfo.offset = SP_NULL;
	vbInfo.vertexCount = 6;
	vbInfo.vertices = vertices;

	IndexBufferCreateInfo ibInfo{};
	ibInfo.dataType = IndexBufferDataType::UByte;
	ibInfo.storageType = IndexBufferStorageType::Dynamic;
	ibInfo.indexCount = 6;
	ibInfo.indices = indices;

	VertexArray va;
	va.LinkVBO(VertexBuffer::Create(&vbInfo));

	va.PushAttrib(0, 3, false, SP_NULL);
	va.PushAttrib(1, 3, false, sizeof(vec3));
	va.PushAttrib(2, 2, false, sizeof(vec3) * 2);

	va.LinkIBO(IndexBuffer::Create(&ibInfo));
	
	RendererStatistics renderStats{};
	renderStats.drawCalls = 1;
	renderStats.triangleCount = va.GetLinkedVBOs()[0]->GetVertexCount() / SP_VERTICES_PER_TRIANGLE;
	renderStats.vertices = va.GetLinkedVBOs()[0]->GetVertexCount();

	Renderer renderer;
	renderer.SetClearColor({ 0.1f, 0.1f, 0.11f });
	renderer.SubmitStats(&renderStats);
	
	f32 moveSpeed{ 0.05f };
	f32 mixValue{ 0.5f };
	u32 frameCount{};

	while (!m_Window->Closed())
	{
		framebuffer.Bind();
		renderer.RenderClear();

		shader.SetUniform("u_Model", model);
		shader.SetUniform("u_MixValue", mixValue);
		m_Window->ProcessInput(model, moveSpeed, mixValue, shader);	

		texture.Bind(0);
		texture2.Bind(1);
		va.Bind();

		renderer.Render(PrimitiveType::Triangles, va.GetLinkedVBOs()[0]->GetVertexCount(), va.GetIBODataType());

		renderer.SwapFrameBuffers();
		framebuffer.Unbind();

		m_Window->CreateEditorGUIFrame(framebuffer, frameCount, renderer.GetStats());

		frameCount++;
	}

	va.Destroy();
	shader.Destroy();
}