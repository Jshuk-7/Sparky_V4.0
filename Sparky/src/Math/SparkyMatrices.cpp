#include "SparkyMatrices.h"

Sparky::mat4::mat4() noexcept
{
	for (u32 i = 0; i < 4 * 4; i++)
		elements[i] = 0.0f;
}

Sparky::mat4::mat4(f32 diagonal) noexcept
{
	for (u32 i = 0; i < 4 * 4; i++)
		elements[i] = 0.0f;

	//! elements[row + col * width]
	elements[0 + 0 * 4] = diagonal;
	elements[1 + 1 * 4] = diagonal;
	elements[2 + 2 * 4] = diagonal;
	elements[3 + 3 * 4] = diagonal;
}

Sparky::mat4 Sparky::mat4::identity() noexcept
{
	return mat4(1.0f);
}

Sparky::mat4& Sparky::mat4::multiply(const mat4& other) noexcept
{
	for (u32 row = 0; row < 4; row++)
	{
		for (u32 col = 0; col < 4; col++)
		{
			f32 sum = 0.0f;

			for (u32 i = 0; i < 4; i++)
				sum += elements[col + i * 4] * other.elements[i + row * 4];

			elements[col + row * 4] = sum;
		}
	}

	return *this;
}

Sparky::mat4 Sparky::operator*(mat4 left, const mat4& right) noexcept
{
	return left.multiply(right);
}

Sparky::mat4& Sparky::mat4::operator*=(const mat4& other) noexcept
{
	return multiply(other);
}

Sparky::mat4& Sparky::mat4::operator=(const mat4& other) noexcept
{
	for (u32 i = 0; i < 16; i++)
	{
		elements[i] = other.elements[i];
	}

	return *this;
}

std::ostream& Sparky::operator<<(std::ostream& stream, const mat4& matrix) noexcept
{
	return stream << "mat4: [  1  " << matrix.elements[0] << ' ' << matrix.elements[1] << ' ' << matrix.elements[2] << ' ' << matrix.elements[3]
				  << ",\n\t\t\t\t\t2  " << matrix.elements[4] << ' ' << matrix.elements[5] << ' ' << matrix.elements[6] << ' ' << matrix.elements[7]
				  << ",\n\t\t\t\t\t3  " << matrix.elements[8] << ' ' << matrix.elements[9] << ' ' << matrix.elements[10] << ' ' << matrix.elements[11]
				  << ",\n\t\t\t\t\t4  " << matrix.elements[12] << ' ' << matrix.elements[13] << ' ' << matrix.elements[14] << ' ' << matrix.elements[15] << "  ]";
}

Sparky::mat4 Sparky::mat4::orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far) noexcept
{
	mat4 result(1.0f);

	result.elements[0 + 0 * 4] = 2.0f / (right - left);
	result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
	result.elements[2 + 2 * 4] = 2.0f / (near - far);

	result.elements[3 + 0 * 4] = (left + right) / (left - right);
	result.elements[3 + 1 * 4] = (bottom + top) / (bottom - top);
	result.elements[3 + 2 * 4] = (far + near) / (far - near);

	return result;
}

Sparky::mat4 Sparky::mat4::perspective(f32 FOV, f32 aspectRatio, f32 near, f32 far) noexcept
{
	mat4 result(1.0f);

	float q = 1.0f / tan(deg2rad(0.5f * FOV));
	float a = q / aspectRatio;

	float b = (near + far) / (near - far);
	float c = (2.0f * near * far) / (near - far);

	result.elements[0 + 0 * 4] = a;
	result.elements[1 + 1 * 4] = q;
	result.elements[2 + 2 * 4] = b;
	result.elements[2 + 3 * 4] = -1.0f;
	result.elements[3 + 2 * 4] = c;

	return result;
}

Sparky::mat4 Sparky::mat4::translate(const vec3& translation) noexcept
{
	mat4 result(1.0f);

	result.elements[0 + 3 * 4] = translation.x;
	result.elements[1 + 3 * 4] = translation.y;
	result.elements[2 + 3 * 4] = translation.z;

	return result;
}

Sparky::mat4 Sparky::mat4::rotate(f32 angle, const vec3& axis) noexcept
{
	mat4 result(1.0f);

	f32 r = deg2rad(angle);
	f32 c = cos(r);
	f32 s = sin(r);
	f32 omc = 1.0f - c;

	f32 x = axis.x;
	f32 y = axis.y;
	f32 z = axis.z;

	result.elements[0 + 0 * 4] = x * omc + c;
	result.elements[1 + 0 * 4] = y * x * omc + z * s;
	result.elements[2 + 0 * 4] = x * z * omc - y * s;

	result.elements[0 + 1 * 4] = x * y * omc - z * s;
	result.elements[1 + 1 * 4] = y * omc + c;
	result.elements[2 + 1 * 4] = y * z * omc + x * s;

	result.elements[0 + 2 * 4] = x * z * omc + y * s;
	result.elements[1 + 2 * 4] = y * z * omc - x * s;
	result.elements[2 + 2 * 4] = z * omc + c;

	return result;
}

Sparky::mat4 Sparky::mat4::scale(const vec3& scale) noexcept
{
	mat4 result(1.0f);

	result.elements[0 + 0 * 4] = scale.x;
	result.elements[1 + 1 * 4] = scale.y;
	result.elements[2 + 2 * 4] = scale.z;

	return result;
}