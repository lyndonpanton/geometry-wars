#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <tuple>

#include "Component.hpp"

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

	// constructors
	Entity(const size_t&, const std::string&);
public:
	// getters
	bool getIsActive() const;
	size_t getId() const;
	const std::string& getTag() const;

	template <typename T>
	T& get();
	template <typename T>
	const T& get() const;

	// setters
	void destroy();

	// custom
	template <typename T, typename... TArgs>
	T& add(TArgs&&... m_args);
	template <typename T>
	bool has() const;
	template <typename T>
	void remove();
};

#endif
