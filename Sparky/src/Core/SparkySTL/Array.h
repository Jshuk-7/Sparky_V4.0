#pragma once

#include "Config/Defines.h"

namespace Sparky::stl {
	template <typename T, size_t S>
	class Array
	{
	public:
		inline constexpr size_t Size() const noexcept { return S; }

		inline size_t Bytes() const noexcept { return S * sizeof(T); }

		_SP_NODISCARD T& operator[](size_t index) noexcept {
#ifdef SP_DEBUG
			if (!(index < S))
				__debugbreak();
#endif

			return m_Data[index];
		}

		_SP_NODISCARD const T& operator[](size_t index) const noexcept {
#ifdef SP_DEBUG
			if (!(index < S))
				__debugbreak();
#endif

			return m_Data[index];
		}

		T* Data() { return m_Data; }
		const T* Data() const { return m_Data; }

	private:
		T m_Data[S];
	};
}