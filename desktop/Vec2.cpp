#include "Vec2.h"

template <typename T>
Vec2<T>::Vec2() { }

template <typename T>
Vec2<T>::Vec2(T xin, T yin)
	: x(xin)
	, y(yin)
{ }

template <typename T>
Vec2<T>::Vec2(const Vec2& vector)
	: x(vector.x)
	, y(vector.y)
{ }

template <typename T>
Vec2<T>::Vec2(const sf::Vector2<T>& vector)
	: x(vector.x)
	, y(vector.y)
{ }

template <typename T>
Vec2<T>::operator sf::Vector2<T>()
{
	return sf::Vector2<T>(x, y);
}

template <typename T>
Vec2<T> Vec2<T>::operator+(const Vec2& vector) const
{
	return Vec2<T>(x + vector.x, y + vector.y);
}

template <typename T>
Vec2<T> Vec2<T>::operator-(const Vec2& vector) const
{
	return Vec2<T>(x - vector.x, y - vector.y);
}

template <typename T>
Vec2<T> Vec2<T>::operator*(const float scalar) const
{
	return Vec2<T>(x * scalar, y * scalar);
}

template <typename T>
Vec2<T> Vec2<T>::operator/(const float scalar) const
{
	return Vec2<T>(x / scalar, y / scalar);
}

template <typename T>
void Vec2<T>::operator+=(const Vec2& vector)
{
	x += vector.x;
	y += vector.y;
}

template <typename T>
void Vec2<T>::operator-=(const Vec2& vector)
{
	x -= vector.x;
	y -= vector.y;
}

template <typename T>
void Vec2<T>::operator*=(const float& scalar)
{
	x *= scalar.x;
	y *= scalar.y;
}

template <typename T>
void Vec2<T>::operator/=(const float& scalar)
{
	x /= scalar.x;
	y /= scalar.y;
}

template <typename T>
bool Vec2<T>::operator==(const Vec2& vector) const
{
	if (x == vector.x && y == vector.y) return true;

	return false;
}


template <typename T>
bool Vec2<T>::operator!=(const Vec2& vector) const
{
	if (x == vector.x && y == vector.y) return false;

	return true;
}

template <typename T>
float Vec2<T>::distance(const Vec2& vector) const
{
	return sqrtf(pow(x - vector.x, 2) + pow(y - vector.y, 2));
}
