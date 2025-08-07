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
	Vec2(T, T);
	Vec2(const Vec2&);
	Vec2(const sf::Vector2<T>&);

	// getters

	// setters

	// overloads
	operator sf::Vector2<T>();

	Vec2 operator+(const Vec2&) const;
	Vec2 operator-(const Vec2&) const;
	Vec2 operator*(const float&) const;
	Vec2 operator/(const float&) const;

	void operator+=(const Vec2&);
	void operator-=(const Vec2&);
	void operator*=(const float&);
	void operator/=(const float&);

	bool operator==(const Vec2&) const;
	bool operator!=(const Vec2&) const;

	// other
	float distance(const Vec2&) const;
};

using Vec2f = Vec2<float>;

#endif
