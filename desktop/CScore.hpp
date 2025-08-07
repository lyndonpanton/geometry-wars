#include "Component.h"

class CScore : public Component
{

public:
	int score = 0;

	CScore() = default;
	CScore(int s)
		: score(s)
	{ }
};
