#include "Component.h"

class CLifespan : public Component
{

public:
	float lifespan_total = 0;
	float lifespan_remaining = 0;

	CLifespan() = default;
	CLifespan(float lt)
		: lifespan_total(lt)
		, lifespan_remaining(lt)
	{ }
};
