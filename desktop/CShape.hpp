#include "Component.h"

class CShape : Component
{

public:
	sf::CircleShape circle;

	CShape() = default;
	CShape(
		float radius, size_t point_count, const sf::Color& fill_colour,
		const sf::Color& outline_colour, size_t outline_thickness
	)
		: circle(radius, point_count)
	{
		circle.setFillColor(fill_colour);
		circle.setOutlineColor(outline_colour);
		circle.setOutlineThickness(outline_thickness);
		circle.setOrigin(radius, radius);
	}
};
