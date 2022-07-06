#include "SparkyVectors.h"

Sparky::vec2::vec2() noexcept
	: x(0.0f), y(0.0f) { }

Sparky::vec2::vec2(const f32& v) noexcept
	: x(v), y(v) {}

Sparky::vec2::vec2(const f32& x, const f32& y) noexcept
	: x(x), y(y) { }

Sparky::vec2& Sparky::vec2::operator=(const vec2& other) noexcept
{
	x = other.x;
	y = other.y;

	return *this;
}

Sparky::b8 Sparky::vec2::operator==(const vec2& other) const noexcept
{
	return x == other.x && y == other.y;
}

Sparky::b8 Sparky::vec2::operator!=(const vec2& other) const noexcept
{
	return !(*this == other);
}

Sparky::b8 Sparky::vec2::operator>(const vec2& other) const noexcept
{
	return x > other.x && y > other.y;
}

Sparky::b8 Sparky::vec2::operator>=(const vec2& other) const noexcept
{
	return x >= other.x && y >= other.y;
}

Sparky::b8 Sparky::vec2::operator<(const vec2& other) const noexcept
{
	return !(*this > other);
}

Sparky::b8 Sparky::vec2::operator<=(const vec2& other) const noexcept
{
	return !(*this >= other);
}

Sparky::vec2& Sparky::operator+(vec2& left, const vec2& right) noexcept
{
	return left.add(right);
}

Sparky::vec2& Sparky::operator-(vec2& left, const vec2& right) noexcept
{
	return left.subtract(right);
}

Sparky::vec2& Sparky::operator*(vec2& left, const vec2& right) noexcept
{
	return left.multiply(right);
}

Sparky::vec2& Sparky::operator/(vec2& left, const vec2& right) noexcept
{
	return left.divide(right);
}

Sparky::vec2& Sparky::vec2::operator+=(const vec2& other) noexcept
{
	return add(other);
}

Sparky::vec2& Sparky::vec2::operator-=(const vec2& other) noexcept
{
	return subtract(other);
}

Sparky::vec2& Sparky::vec2::operator*=(const vec2& other) noexcept
{
	return multiply(other);
}

Sparky::vec2& Sparky::vec2::operator/=(const vec2& other) noexcept
{
	return divide(other);
}

std::ostream& Sparky::operator<<(std::ostream& stream, const vec2& vector) noexcept
{
	return stream << "vec2: (" << vector.x << ", " << vector.y << ')';
}

Sparky::vec2& Sparky::vec2::add(const vec2& other) noexcept
{
	x += other.x;
	y += other.y;

	return *this;
}

Sparky::vec2& Sparky::vec2::add(const f32& x, const f32& y) noexcept
{
	this->x += x;
	this->y += y;

	return *this;
}

Sparky::vec2& Sparky::vec2::subtract(const vec2& other) noexcept
{
	x -= other.x;
	y -= other.y;

	return *this;
}

Sparky::vec2& Sparky::vec2::subtract(const f32& x, const f32& y) noexcept
{
	this->x -= x;
	this->y -= y;

	return *this;
}

Sparky::vec2& Sparky::vec2::multiply(const vec2& other) noexcept
{
	x *= other.x;
	y *= other.y;

	return *this;
}

Sparky::vec2& Sparky::vec2::multiply(const f32& x, const f32& y) noexcept
{
	this->x *= x;
	this->y *= y;

	return *this;
}

Sparky::vec2& Sparky::vec2::divide(const vec2& other) noexcept
{
	x /= other.x;
	y /= other.y;

	return *this;
}

Sparky::vec2& Sparky::vec2::divide(const f32& x, const f32& y) noexcept
{
	this->x /= x;
	this->y /= y;

	return *this;
}

Sparky::vec3::vec3() noexcept
	: x(0.0f), y(0.0f), z(0.0f) { }

Sparky::vec3::vec3(const f32& v) noexcept
	: x(v), y(v), z(v) { }

Sparky::vec3::vec3(const f32& x, const f32& y, const f32& z) noexcept
	: x(x), y(y), z(z) { }

Sparky::vec3& Sparky::vec3::operator=(const vec3& other) noexcept
{
	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

Sparky::b8 Sparky::vec3::operator==(const vec3& other) const noexcept
{
	return x == other.x && y == other.y && z == other.z;
}

Sparky::b8 Sparky::vec3::operator!=(const vec3& other) const noexcept
{
	return !(*this == other);
}

Sparky::b8 Sparky::vec3::operator>(const vec3& other) const noexcept
{
	return x > other.x && y > other.y && z > other.z;
}

Sparky::b8 Sparky::vec3::operator>=(const vec3& other) const noexcept
{
	return x >= other.x && y >= other.y && z >= other.z;
}

Sparky::b8 Sparky::vec3::operator<(const vec3& other) const noexcept
{
	return !(*this > other);
}

Sparky::b8 Sparky::vec3::operator<=(const vec3& other) const noexcept
{
	return !(*this >= other);
}

Sparky::vec3& Sparky::operator+(vec3& left, const vec3& right) noexcept
{
	return left.add(right);
}

Sparky::vec3& Sparky::operator-(vec3& left, const vec3& right) noexcept
{
	return left.subtract(right);
}

Sparky::vec3& Sparky::operator*(vec3& left, const vec3& right) noexcept
{
	return left.multiply(right);
}

Sparky::vec3& Sparky::operator/(vec3& left, const vec3& right) noexcept
{
	return left.divide(right);
}

Sparky::vec3& Sparky::vec3::operator+=(const vec3& other) noexcept
{
	return add(other);
}

Sparky::vec3& Sparky::vec3::operator-=(const vec3& other) noexcept
{
	return subtract(other);
}

Sparky::vec3& Sparky::vec3::operator*=(const vec3& other) noexcept
{
	return multiply(other);
}

Sparky::vec3& Sparky::vec3::operator/=(const vec3& other) noexcept
{
	return divide(other);
}

std::ostream& Sparky::operator<<(std::ostream& stream, const vec3& vector) noexcept
{
	return stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ')';
}

Sparky::vec3& Sparky::vec3::add(const vec3& other) noexcept
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Sparky::vec3& Sparky::vec3::add(const f32& x, const f32& y, const f32& z) noexcept
{
	this->x += x;
	this->y += y;
	this->z += z;

	return *this;
}

Sparky::vec3& Sparky::vec3::subtract(const vec3& other) noexcept
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

Sparky::vec3& Sparky::vec3::subtract(const f32& x, const f32& y, const f32& z) noexcept
{
	this->x -= x;
	this->y -= y;
	this->z -= z;

	return *this;
}

Sparky::vec3& Sparky::vec3::multiply(const vec3& other) noexcept
{
	x *= other.x;
	y *= other.y;
	z *= other.z;

	return *this;
}

Sparky::vec3& Sparky::vec3::multiply(const f32& x, const f32& y, const f32& z) noexcept
{
	this->x *= x;
	this->y *= y;
	this->z *= z;

	return *this;
}

Sparky::vec3& Sparky::vec3::divide(const vec3& other) noexcept
{
	x /= other.x;
	y /= other.y;
	z /= other.z;

	return *this;
}

Sparky::vec3& Sparky::vec3::divide(const f32& x, const f32& y, const f32& z) noexcept
{
	this->x /= x;
	this->y /= y;
	this->z /= z;

	return *this;
}

Sparky::vec4::vec4(const f32& v) noexcept
	: x(v), y(v), z(v), w(v) { }

Sparky::vec4::vec4(const f32& x, const f32& y, const f32& z, const f32& w) noexcept
	: x(x), y(y), z(z), w(w) { }

Sparky::vec4& Sparky::vec4::operator=(const vec4& other) noexcept
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;

	return *this;
}

Sparky::b8 Sparky::vec4::operator==(const vec4& other) const noexcept
{
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

Sparky::b8 Sparky::vec4::operator!=(const vec4& other) const noexcept
{
	return !(*this == other);
}

Sparky::b8 Sparky::vec4::operator>(const vec4& other) const noexcept
{
	return x > other.x && y > other.y && z > other.z && w > other.w;
}

Sparky::b8 Sparky::vec4::operator>=(const vec4& other) const noexcept
{
	return x >= other.x && y >= other.y && z >= other.z && w >= other.w;
}

Sparky::b8 Sparky::vec4::operator<(const vec4& other) const noexcept
{
	return !(*this > other);
}

Sparky::b8 Sparky::vec4::operator<=(const vec4& other) const noexcept
{
	return !(*this >= other);
}

Sparky::vec4& Sparky::operator+(vec4& left, const vec4& right) noexcept
{
	return left.add(right);
}

Sparky::vec4& Sparky::operator-(vec4& left, const vec4& right) noexcept
{
	return left.subtract(right);
}

Sparky::vec4& Sparky::operator*(vec4& left, const vec4& right) noexcept
{
	return left.multiply(right);
}

Sparky::vec4& Sparky::operator/(vec4& left, const vec4& right) noexcept
{
	return left.divide(right);
}

Sparky::vec4& Sparky::vec4::operator+=(const vec4& other) noexcept
{
	return add(other);
}

Sparky::vec4& Sparky::vec4::operator-=(const vec4& other) noexcept
{
	return subtract(other);
}

Sparky::vec4& Sparky::vec4::operator*=(const vec4& other) noexcept
{
	return multiply(other);
}

Sparky::vec4& Sparky::vec4::operator/=(const vec4& other) noexcept
{
	return divide(other);
}

std::ostream& Sparky::operator<<(std::ostream& stream, const vec4& vector) noexcept
{
	return stream << "vec4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ')';
}

Sparky::vec4& Sparky::vec4::add(const vec4& other) noexcept
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;

	return *this;
}

Sparky::vec4& Sparky::vec4::add(const f32& x, const f32& y, const f32& z, const f32& w) noexcept
{
	this->x += x;
	this->y += y;
	this->z += z;
	this->w += w;

	return *this;
}

Sparky::vec4& Sparky::vec4::subtract(const vec4& other) noexcept
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;

	return *this;
}

Sparky::vec4& Sparky::vec4::subtract(const f32& x, const f32& y, const f32& z, const f32& w) noexcept
{
	this->x -= x;
	this->y -= y;
	this->z -= z;
	this->w -= w;

	return *this;
}

Sparky::vec4& Sparky::vec4::multiply(const vec4& other) noexcept
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	w *= other.w;

	return *this;
}

Sparky::vec4& Sparky::vec4::multiply(const f32& x, const f32& y, const f32& z, const f32& w) noexcept
{
	this->x *= x;
	this->y *= y;
	this->z *= z;
	this->w *= w;

	return *this;
}

Sparky::vec4& Sparky::vec4::divide(const vec4& other) noexcept
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	w /= other.w;

	return *this;
}

Sparky::vec4& Sparky::vec4::divide(const f32& x, const f32& y, const f32& z, const f32& w) noexcept
{
	this->x /= x;
	this->y /= y;
	this->z /= z;
	this->w /= w;

	return *this;
}