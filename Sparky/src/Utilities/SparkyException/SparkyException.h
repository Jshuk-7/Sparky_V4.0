#pragma once

#include <exception>
#include <string>

#include "Config/Defines.h"

namespace Sparky {
	class SparkyException : public std::exception
	{
	public:
		SparkyException(i32 line, const i8* file) noexcept;
		const i8* what() const noexcept override;
		virtual const i8* GetType() const noexcept;
		i32 GetLine() const noexcept;
		const std::string& GetFile() const noexcept;
		std::string GetOriginString() const noexcept;

	private:
		i32 m_Line;
		std::string m_File;

	protected:
		mutable std::string m_WhatBuffer;
	};
}