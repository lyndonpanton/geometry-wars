#ifndef COMPONENT_H
#define COMPONENT_H

#pragma once

#include <SFML/Graphics.hpp>

#include "Vec2.h"

class Component
{

public:
	bool exists = false;
};

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
	{
	}
};

class CShape : public Component
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

class CCollision : public Component
{

public:
	float radius = 0;

	CCollision() = default;
	CCollision(float r)
		: radius(r)
	{
	}

};

class CScore : public Component
{

public:
	int score = 0;

	CScore() = default;
	CScore(int s)
		: score(s)
	{
	}
};

class CLifespan : public Component
{

public:
	float lifespan_total = 0;
	float lifespan_remaining = 0;

	CLifespan() = default;
	CLifespan(float lt)
		: lifespan_total(lt)
		, lifespan_remaining(lt)
	{
	}
};

class CInput : public Component
{

public:
	bool is_up_pressed = false;
	bool is_right_pressed = false;
	bool is_down_pressed = false;
	bool is_left_pressed = false;
	bool is_shoot_pressed = false;

	CInput() = default;
};

class CSpecialAbility : public Component
{

public:
	// TODO
};



#endif
