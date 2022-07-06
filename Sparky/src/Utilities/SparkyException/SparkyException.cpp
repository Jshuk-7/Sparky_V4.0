#include <sstream>

#include "SparkyException.h"

Sparky::SparkyException::SparkyException(i32 line, const i8* file) noexcept
	: m_Line(line), m_File(file) { }

const Sparky::i8* Sparky::SparkyException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << '\n'
		<< GetOriginString();

	m_WhatBuffer = oss.str();
	return m_WhatBuffer.c_str();
}

const Sparky::i8* Sparky::SparkyException::GetType() const noexcept
{
	return "Sparky Exception";
}

Sparky::i32 Sparky::SparkyException::GetLine() const noexcept
{
	return m_Line;
}

const std::string& Sparky::SparkyException::GetFile() const noexcept
{
	return m_File;
}

std::string Sparky::SparkyException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[FILE]: " << m_File << '\n'
	    << "[LINE]: " << m_Line;

	return oss.str();
}