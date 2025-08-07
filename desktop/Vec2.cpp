#include "Vec2.h"

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
Vec2<T> Vec2<T>::operator*(const float& scalar) const
{
	return Vec2<T>(x * scalar, y * scalar);
}

template <typename T>
Vec2<T> Vec2<T>::operator/(const float& scalar) const
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
	x *= scalar;
	y *= scalar;
}

template <typename T>
void Vec2<T>::operator/=(const float& scalar)
{
	x /= scalar;
	y /= scalar;
}

template <typename T>
bool Vec2<T>::operator==(const Vec2& vector) const
{
	return (x == vector.x) && (y == vector.y);
}

template <typename T>
bool Vec2<T>::operator!=(const Vec2& vector) const
{
	return !((x == vector.x) && (y == vector.y));
}

template <typename T>
float Vec2<T>::distance(const Vec2& vector) const
{
	return sqrtf(
		(x - vector.x) * (x - vector.x)
		+ (y - vector.y) * (y - vector.y)
	);
}
