#pragma once

#include <iostream>

#include "SparkyMath.h"

namespace Sparky {
	struct mat4
	{
		union {
			f32 elements[4 * 4];
			vec4 columns[4];
		};

		mat4() noexcept;
		mat4(f32 diagonal) noexcept;

		static mat4 identity() noexcept;

		mat4& multiply(const mat4& other) noexcept;
		friend mat4 operator*(mat4 left, const mat4& right) noexcept;
		mat4& operator*=(const mat4& other) noexcept;
		mat4& operator=(const mat4& other) noexcept;

		friend std::ostream& operator<<(std::ostream& stream, const mat4& matrix) noexcept;

		//! Projection Matrices

		static mat4 orthographic(
			f32 left = -2.0f,
			f32 right = 2.0f,
			f32 bottom = -1.5f,
			f32 top = 1.5f,
			f32 near = -1.0f,
			f32 far = 1.0f
		) noexcept;

		static mat4 perspective(f32 FOV, f32 aspectRatio, f32 near, f32 far) noexcept;
		
		//! Transformation Matrices

		static mat4 translate(const vec3& translation) noexcept;
		static mat4 rotate(f32 angle, const vec3& axis) noexcept;
		static mat4 scale(const vec3& scale) noexcept;
	};
}