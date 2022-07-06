#pragma once

#define GLFW_INCLUDE_OPENGL
#include <GLFW/glfw3.h>

namespace Sparky {
	#define SP_EXIT_SUCCESS 0
	#define SP_EXIT_FAILURE 1
	#define SP_NULL 0
	#define SP_NULL_HANDLE nullptr
	#define _SP_NODISCARD _NODISCARD

	#define SP_TRUE true
	#define SP_FALSE false

	/// @brief Unsigned 8-bit integer
	typedef unsigned char u8;

	/// @brief Unsigned 16-bit integer
	typedef unsigned short u16;

	/// @brief Unsigned 32-bit integer
	typedef unsigned int u32;

	/// @brief Unsigned 64-bit integer
	typedef unsigned long long u64;

	/// @brief Signed 8-bit integer
	typedef char i8;

	/// @brief Signed 16-bit integer
	typedef short i16;

	/// @brief Signed 32-bit integer
	typedef int i32;

	/// @brief Signed 64-bit integer
	typedef long long i64;

	/// @brief 32-bit floating point number
	typedef float f32;

	/// @brief 64-bit floating point number
	typedef double f64;

	/// @brief 8-bit boolean (0 : False || 1 : True)
	typedef bool b8;

	struct Version {
		u32 major, minor, patch;
	};
}