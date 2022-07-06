#pragma once

#include <iostream>

#include "Config/Defines.h"

namespace Sparky {
	struct vec2 {
		union { f32 x, u, s; };
		union { f32 y, v, t; };

		vec2() noexcept;
		vec2(const f32& v) noexcept;
		vec2(const f32& x, const f32& y) noexcept;

		vec2& operator=(const vec2& other) noexcept;

		b8 operator==(const vec2& other) const noexcept;
		b8 operator!=(const vec2& other) const noexcept;
		b8 operator>(const vec2& other) const noexcept;
		b8 operator>=(const vec2& other) const noexcept;
		b8 operator<(const vec2& other) const noexcept;
		b8 operator<=(const vec2& other) const noexcept;

		friend vec2& operator+(vec2& left, const vec2& right) noexcept;
		friend vec2& operator-(vec2& left, const vec2& right) noexcept;
		friend vec2& operator*(vec2& left, const vec2& right) noexcept;
		friend vec2& operator/(vec2& left, const vec2& right) noexcept;

		vec2& operator+=(const vec2& other) noexcept;
		vec2& operator-=(const vec2& other) noexcept;
		vec2& operator*=(const vec2& other) noexcept;
		vec2& operator/=(const vec2& other) noexcept;

		friend std::ostream& operator<<(std::ostream& stream, const vec2& vector) noexcept;

		vec2& add(const vec2& other) noexcept;
		vec2& add(const f32& x, const f32& y) noexcept;

		vec2& subtract(const vec2& other) noexcept;
		vec2& subtract(const f32& x, const f32& y) noexcept;

		vec2& multiply(const vec2& other) noexcept;
		vec2& multiply(const f32& x, const f32& y) noexcept;

		vec2& divide(const vec2& other) noexcept;
		vec2& divide(const f32& x, const f32& y) noexcept;
	};

	struct vec3 {
		union { f32 x, r; };
		union { f32 y, g; };
		union { f32 z, b; };

		vec3() noexcept;
		vec3(const f32& v) noexcept;
		vec3(const f32& x, const f32& y, const f32& z) noexcept;

		vec3& operator=(const vec3& other) noexcept;

		b8 operator==(const vec3& other) const noexcept;
		b8 operator!=(const vec3& other) const noexcept;
		b8 operator>(const vec3& other) const noexcept;
		b8 operator>=(const vec3& other) const noexcept;
		b8 operator<(const vec3& other) const noexcept;
		b8 operator<=(const vec3& other) const noexcept;

		friend vec3& operator+(vec3& left, const vec3& right) noexcept;
		friend vec3& operator-(vec3& left, const vec3& right) noexcept;
		friend vec3& operator*(vec3& left, const vec3& right) noexcept;
		friend vec3& operator/(vec3& left, const vec3& right) noexcept;

		vec3& operator+=(const vec3& other) noexcept;
		vec3& operator-=(const vec3& other) noexcept;
		vec3& operator*=(const vec3& other) noexcept;
		vec3& operator/=(const vec3& other) noexcept;

		friend std::ostream& operator<<(std::ostream& stream, const vec3& vector) noexcept;

		vec3& add(const vec3& other) noexcept;
		vec3& add(const f32& x, const f32& y, const f32& z) noexcept;

		vec3& subtract(const vec3& other) noexcept;
		vec3& subtract(const f32& x, const f32& y, const f32& z) noexcept;

		vec3& multiply(const vec3& other) noexcept;
		vec3& multiply(const f32& x, const f32& y, const f32& z) noexcept;

		vec3& divide(const vec3& other) noexcept;
		vec3& divide(const f32& x, const f32& y, const f32& z) noexcept;
	};

	struct vec4 {
		//! XYZW mapped to RGBA
		union { f32 x, r; };
		union { f32 y, g; };
		union { f32 z, b; };
		union { f32 w, a; };

		vec4() noexcept = default;
		vec4(const f32& v) noexcept;
		vec4(const f32& x, const f32& y, const f32& z, const f32& w) noexcept;

		vec4& operator=(const vec4& other) noexcept;

		b8 operator==(const vec4& other) const noexcept;
		b8 operator!=(const vec4& other) const noexcept;
		b8 operator>(const vec4& other) const noexcept;
		b8 operator>=(const vec4& other) const noexcept;
		b8 operator<(const vec4& other) const noexcept;
		b8 operator<=(const vec4& other) const noexcept;

		friend vec4& operator+(vec4& left, const vec4& right) noexcept;
		friend vec4& operator-(vec4& left, const vec4& right) noexcept;
		friend vec4& operator*(vec4& left, const vec4& right) noexcept;
		friend vec4& operator/(vec4& left, const vec4& right) noexcept;

		vec4& operator+=(const vec4& other) noexcept;
		vec4& operator-=(const vec4& other) noexcept;
		vec4& operator*=(const vec4& other) noexcept;
		vec4& operator/=(const vec4& other) noexcept;

		friend std::ostream& operator<<(std::ostream& stream, const vec4& vector) noexcept;

		vec4& add(const vec4& other) noexcept;
		vec4& add(const f32& x, const f32& y, const f32& z, const f32& w) noexcept;

		vec4& subtract(const vec4& other) noexcept;
		vec4& subtract(const f32& x, const f32& y, const f32& z, const f32& w) noexcept;

		vec4& multiply(const vec4& other) noexcept;
		vec4& multiply(const f32& x, const f32& y, const f32& z, const f32& w) noexcept;

		vec4& divide(const vec4& other) noexcept;
		vec4& divide(const f32& x, const f32& y, const f32& z, const f32& w) noexcept;
	};
}