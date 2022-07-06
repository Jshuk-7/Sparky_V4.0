#pragma once

#include "Config/Defines.h"

namespace Sparky::stl {
	template <typename Vector>
	class _VectorIterator
	{
	public:
		using ValueType      = typename Vector::ValueType;
		using PointerType    = ValueType*;
		using ReferenceType  = ValueType&;

	public:
		_VectorIterator(PointerType ptr)
			: m_Ptr(ptr) { }

		_VectorIterator& operator++()
		{
			m_Ptr++;
			return *this;
		}

		_VectorIterator operator++(i32)
		{
			_VectorIterator iterator = *this;
			++(*this);
			return iterator;
		}

		_VectorIterator& operator--()
		{
			m_Ptr--;
			return *this;
		}

		_VectorIterator operator--(i32)
		{
			_VectorIterator iterator = *this;
			--(*this);
			return iterator;
		}

		ReferenceType operator[](i32 index)
		{
			return *(m_Ptr + index);
		}

		PointerType operator->()
		{
			return m_Ptr;
		}

		ReferenceType operator*()
		{
			return *m_Ptr;
		}

		b8 operator==(const _VectorIterator& other) const
		{
			return m_Ptr == other.m_Ptr;
		}

		b8 operator!=(const _VectorIterator& other) const
		{
			return !(*this == other);
		}

	private:
		PointerType m_Ptr;

	};

	template <typename T>
	class Vector
	{
	public:
		using ValueType = T;
		using Iterator = _VectorIterator<Vector<T>>;

	public:
		Vector() noexcept
		{
			ReAlloc(2);
		}

		~Vector() noexcept
		{
			Clear();
			::operator delete(m_Data, m_Capacity * sizeof(T));
		}

		void PushBack(const T& value) noexcept
		{
			if (m_Size >= m_Capacity)
				ReAlloc(m_Capacity * 2);

			m_Data[m_Size] = value;
			m_Size++;
		}

		void PushBack(T&& value) noexcept
		{
			if (m_Size >= m_Capacity)
				ReAlloc(m_Capacity * 2);

			m_Data[m_Size] = std::move(value);
			m_Size++;
		}

		template <typename... Args>
		T& EmplaceBack(Args&&... args) noexcept
		{
			if (m_Size >= m_Capacity)
				ReAlloc(m_Capacity << 1);

			new(&m_Data[m_Size]) T(std::forward<Args>(args)...);
			return m_Data[m_Size++];
		}

		void PopBack() noexcept
		{
			if (m_Size > SP_NULL)
			{
				m_Size--;
				m_Data[m_Size].~T();
			}
		}

		void Clear() noexcept
		{
			if (m_Size > SP_NULL)
			{
				for (size_t i = 0; i < m_Size; i++)
					m_Data[i].~T();
			}

			m_Size = 0;
		}

		bool Empty() const noexcept
		{
			return m_Size == SP_NULL;
		}

		const T& operator[](size_t index) const noexcept
		{
#ifdef SP_DEBUG
			if (index > m_Size)
				__debugbreak();
#endif

			return m_Data[index];
		}

		T& operator[](size_t index) noexcept
		{
#ifdef SP_DEBUG
			if (index > m_Size)
				__debugbreak();
#endif

			return m_Data[index];
		}

		inline constexpr size_t Size() const noexcept { return m_Size; }

		inline size_t Bytes() const noexcept { return m_Size * sizeof(T); }

		Iterator begin()
		{
			return Iterator(m_Data);
		}

		Iterator end()
		{
			return Iterator(m_Data + m_Size);
		}

	private:
		void ReAlloc(size_t newCapacity) noexcept
		{
			T* newBlock = (T*)::operator new(newCapacity * sizeof(T));

			if (newCapacity < m_Size)
				m_Size = newCapacity;

			for (size_t i = 0; i < m_Size; i++)
				new(&newBlock[i]) T(std::move(m_Data[i]));

			for (size_t i = 0; i < m_Size; i++)
				m_Data[i].~T();

			::operator delete(m_Data, m_Capacity * sizeof(T));
			m_Data = newBlock;
			m_Capacity = newCapacity;
		}

	private:
		T* m_Data = SP_NULL_HANDLE;
		size_t m_Size;
		size_t m_Capacity;
	};
}