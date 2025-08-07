#include "Component.h"

class CTransform : public Component
{

public:
	Vec2f position = { 0.0f, 0.0f };
	Vec2f velocity = { 0.0f, 0.0f };
	float angle = 0;

	CTransform() = default;
	CTransform(const Vec2f& p, const Vec2f& v, float a)
		: position(p)
		, velocity(v)
		, angle(a)
	{ }
};
