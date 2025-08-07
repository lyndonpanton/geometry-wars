#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#pragma once

#include <memory>

#include "Entity.h"

using EntityVector = std::vector<std::shared_ptr<Entity>>;
using EntityMap = std::map<std::string, EntityVector>;

class EntityManager
{
	EntityVector m_entities;
	EntityVector m_entities_to_add;
	EntityVector m_entities_to_remove;
	EntityMap m_entity_map;
	size_t m_entity_count = 0;

	void removeDeadEntities(EntityVector& entity_vector)
	{
		// remove all dead entitis from the input vector that is called by update
	}
public:
	// constructors
	EntityManager() = default;

	// getters
	const EntityVector& getEntities();
	const EntityVector& getEntities(const std::string& tag);
	const EntityMap& getEntityMap();

	// setters

	// overloading

	// custom
	void update();
	std::shared_ptr<Entity> addEntity(const std::string& tag);
};

#endif
