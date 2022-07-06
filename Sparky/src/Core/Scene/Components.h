#pragma once

#include "Math/SparkyMath.h"

namespace Sparky {
	struct TransformComponent {
		mat4 transform{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const mat4& transform)
			: transform(transform) { }

		operator mat4& () { return transform; }
		operator const mat4& () const { return transform; }
	};

	struct SpriteComponent {
		vec4 color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;
		SpriteComponent(const vec4& color)
			: color(color) { }
	};
}