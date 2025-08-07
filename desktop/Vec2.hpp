#pragma once

#ifndef VEC2_H
#define VEC2_H

#pragma once

#include <math.h>

#include <SFML/Graphics.hpp>

template <typename T>
class Vec2
{

public:
	// members
	T x = 0;
	T y = 0;

	// constructors
	Vec2() = default;
	Vec2(T xin, T yin)
		: x(xin)
		, y(yin)
	{ }
	Vec2(const Vec2& vector)
		: x(vector.x)
		, y(vector.y)
	{ }
	Vec2(const sf::Vector2<T>&vector)
		: x(vector.x)
		, y(vector.y)
	{ }

	// getters

	// setters

	// overloads
	operator sf::Vector2<T>()
	{
		return sf::Vector2<T>(x, y);
	}

	Vec2 operator+(const Vec2& vector) const
	{
		return Vec2(x + vector.x, y + vector.y);
	}

	Vec2 operator-(const Vec2& vector) const
	{
		return Vec2(x - vector.x, y - vector.y);
	}

	Vec2 operator*(const float& scalar) const
	{
		return Vec2(x * scalar, y * scalar);
	}

	Vec2 operator/(const float& scalar) const
	{
		return Vec2(x / scalar, y / scalar);
	}

	void operator+=(const Vec2& vector)
	{
		x += vector.x;
		y += vector.y;
	}

	void operator-=(const Vec2& vector)
	{
		x -= vector.x;
		y -= vector.y;
	}

	void operator*=(const float& scalar)
	{
		x *= scalar;
		y *= scalar;
	}

	void operator/=(const float& scalar)
	{
		x /= scalar;
		y /= scalar;
	}

	bool operator==(const Vec2& vector) const
	{
		return (x == vector.x) && (y == vector.y);
	}

	bool operator!=(const Vec2& vector) const
	{
		return !((x == vector.x) && (y == vector.y));
	}

	// other
	float distance(const Vec2& vector) const
	{
		return sqrtf(
			(x - vector.x) * (x - vector.x)
			+ (y - vector.y) * (y - vector.y)
		);
	}
};

using Vec2f = Vec2<float>;

#endif
