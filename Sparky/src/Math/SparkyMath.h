#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "SparkyVectors.h"
#include "SparkyMatrices.h"
#include "Config/Defines.h"

namespace Sparky {
	struct Vertex {
		vec3 pos;
		vec3 color;
		vec2 texCoord;
	};

	inline f32 deg2rad(f32 degrees)
	{
		return degrees * (f32)(M_PI / 180.0f);
	}
}