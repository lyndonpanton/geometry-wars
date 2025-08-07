#pragma once

#include <string>
#include <tuple>

#include "Component.h"
#include "CCollision.hpp"
#include "CInput.hpp"
#include "CLifespan.hpp"
#include "CScore.hpp"
#include "CShape.hpp"
#include "CSpecialAbility.hpp"
#include "CTransform.hpp"

using ComponentTuple = std::tuple<
	CTransform,
	CShape,
	CCollision,
	CInput,
	CScore,
	CLifespan,
	CSpecialAbility
>;

class Entity
{
	friend class EntityManager;

	ComponentTuple m_components;
	bool m_is_active = true;
	std::string m_tag = "default";
	size_t m_id = 0;

	// private constructor
	Entity(const size_t&, const std::string&);
public:
	// constuctor

	// getters
	bool getIsActive() const;
	size_t getId() const;
	const std::string& getTag() const;

	// setters
	void destroy();

	// overloads

	// other
	template <typename T, typename... TArgs>
	T& add(TArgs&&... m_args);
	template <typename T>
	T& get();
	template <typename T>
	const T& get() const;
	template <typename T>
	bool has() const;
	template <typename T>
	void remove();
};
