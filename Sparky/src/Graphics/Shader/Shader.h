#pragma once

#include <string>

#include "Config/Defines.h"
#include "Math/SparkyMath.h"

namespace Sparky {
	struct ShaderProgramCreateInfo {
		const i8* pVertexShaderFilepath;
		const i8* pFragmentShaderFilepath;
	};

	enum class ShaderType {
		Vertex   = 0,
		Fragment = 1
	};

	class Shader
	{
	public:
		Shader(const ShaderProgramCreateInfo* createInfo) noexcept;
		void Destroy() noexcept;

		void Enable() const noexcept;
		void Disable() const noexcept;

		void SetUniform(const std::string& uniformName, i32 v) const noexcept;
		void SetUniform(const std::string& uniformName, u8 v) const noexcept;
		void SetUniform(const std::string& uniformName, u32 v) const noexcept;
		void SetUniform(const std::string& uniformName, f32 v) const noexcept;
		void SetUniform(const std::string& uniformName, f64 v) const noexcept;
		void SetUniform(const std::string& uniformName, b8 v) const noexcept;
		void SetUniform(const std::string& uniformName, const vec2& vector) const noexcept;
		void SetUniform(const std::string& uniformName, const vec3& vector) const noexcept;
		void SetUniform(const std::string& uniformName, const vec4& vector) const noexcept;
		void SetUniform(const std::string& uniformName, const mat4& matrix) const noexcept;

		void ReCompile();

	private:
		b8 CreateProgram();

		b8 CompileShader(u32& shader, const std::string& filename, ShaderType type) const noexcept;
		i32 GetUniformLocation(const std::string& uniform) const noexcept;

	private:
		ShaderProgramCreateInfo m_CreateInfo;
		u32 m_Id;
	};
}