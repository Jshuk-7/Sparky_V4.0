#define GLFW_INCLUDE_OPENGL
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Utilities/Utilities.h"

#include <fstream>

Sparky::Shader::Shader(const ShaderProgramCreateInfo* createInfo) noexcept
	: m_CreateInfo(*createInfo)
{
	if (CreateProgram() == SP_TRUE)
	{
		Enable();
		SP_TRACE("Shader compiled and linked successfully!");
	}
	else SP_FATAL("Shader failed to compile and link!");
}

void Sparky::Shader::Destroy() noexcept
{
	if (m_Id);
		glDeleteProgram(m_Id);
}

void Sparky::Shader::Enable() const noexcept
{
	if (m_Id)
		glUseProgram(m_Id);
}

void Sparky::Shader::Disable() const noexcept
{
	glUseProgram(SP_NULL);
}

void Sparky::Shader::SetUniform(const std::string& uniformName, i32 v) const noexcept
{
	glProgramUniform1i(m_Id, GetUniformLocation(uniformName), v);
}

void Sparky::Shader::SetUniform(const std::string& uniformName, u8 v) const noexcept
{
	glProgramUniform1ui(m_Id, GetUniformLocation(uniformName), v);
}

void Sparky::Shader::SetUniform(const std::string& uniformName, u32 v) const noexcept
{
	glProgramUniform1ui(m_Id, GetUniformLocation(uniformName), v);
}

void Sparky::Shader::SetUniform(const std::string& uniformName, f32 v) const noexcept
{
	glProgramUniform1f(m_Id, GetUniformLocation(uniformName), v);
}

void Sparky::Shader::SetUniform(const std::string& uniformName, f64 v) const noexcept
{
	glProgramUniform1f(m_Id, GetUniformLocation(uniformName), (f64)v);
}

void Sparky::Shader::SetUniform(const std::string& uniformName, b8 v) const noexcept
{
	glProgramUniform1i(m_Id, GetUniformLocation(uniformName), (u32)v);
}

void Sparky::Shader::SetUniform(const std::string& uniformName, const vec2& vector) const noexcept
{
	glProgramUniform2f(m_Id, GetUniformLocation(uniformName), vector.x, vector.y);
}

void Sparky::Shader::SetUniform(const std::string& uniformName, const vec3& vector) const noexcept
{
	glProgramUniform3f(m_Id, GetUniformLocation(uniformName), vector.x, vector.y, vector.z);
}

void Sparky::Shader::SetUniform(const std::string& uniformName, const vec4& vector) const noexcept
{
	glProgramUniform4f(m_Id, GetUniformLocation(uniformName), vector.x, vector.y, vector.z, vector.w);
}

void Sparky::Shader::SetUniform(const std::string& uniformName, const mat4& matrix) const noexcept
{
	glProgramUniformMatrix4fv(m_Id, GetUniformLocation(uniformName), 1, false, matrix.elements);
}

void Sparky::Shader::ReCompile()
{
	Destroy();

	if (CreateProgram() == SP_TRUE)
	{
		Enable();
		SP_TRACE("Shader hot reload successful!");

		SetUniform("u_Proj", mat4::orthographic(-2.75f, 2.75f));
	}
	else SP_FATAL("Shader hot reload unsuccessful!");
}

Sparky::b8 Sparky::Shader::CreateProgram()
{
	u32 vertexShader{};
	u32 fragmentShader{};

	int  success{};
	char infoLog[512]{};

	if (!CompileShader(vertexShader, m_CreateInfo.pVertexShaderFilepath, ShaderType::Vertex)) return SP_FALSE;
	if (!CompileShader(fragmentShader, m_CreateInfo.pFragmentShaderFilepath, ShaderType::Fragment)) return SP_FALSE;

	m_Id = glCreateProgram();

	glAttachShader(m_Id, vertexShader);
	glAttachShader(m_Id, fragmentShader);
	glLinkProgram(m_Id);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glGetProgramiv(m_Id, GL_LINK_STATUS, &success);

	if (!success)
	{
		glDisable(GL_DEBUG_OUTPUT);
		glGetProgramInfoLog(m_Id, 512, SP_NULL, infoLog);
		SP_FATAL(infoLog);
		throw SparkyException(__LINE__, __FILE__);
		return SP_FALSE;
	}

	return SP_TRUE;
}

Sparky::b8 Sparky::Shader::CompileShader(u32& shader, const std::string& filename, ShaderType type) const noexcept
{
	std::string src;
	std::string line;

	int success{};
	i8 infoLog[512]{};
	i32 shaderType = static_cast<i32>(type);

	std::ifstream file{ filename };

	if (file.is_open())
	{
		while (std::getline(file, line))
			src += line + '\n';
	}
	else
	{
		glDisable(GL_DEBUG_OUTPUT);
		SP_FATAL("Failed to open " + (std::string)(shaderType == 0 ? "vertex" : "fragment") + " shader file from: /" + filename);
		return SP_FALSE;
	}

	file.close();

	shader = glCreateShader(
		(shaderType == 0) ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER
	);

	const char* shaderSrc = src.c_str();

	glShaderSource(shader, 1, &shaderSrc, nullptr);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glDisable(GL_DEBUG_OUTPUT);
		glGetShaderInfoLog(shader, 512, SP_NULL, infoLog);
		SP_FATAL(infoLog);
		return SP_FALSE;
	}
	else return SP_TRUE;
}

Sparky::i32 Sparky::Shader::GetUniformLocation(const std::string& uniform) const noexcept
{
	return glGetUniformLocation(m_Id, uniform.c_str());
}