#pragma once

#include <memory>

#include "Entity.h"

using EntityVector = std::vector<std::shared_ptr<Entity>>;
using EntityMap = std::map<std::string, EntityVector>;

#include <algorithm>

class EntityManager
{
	EntityVector m_entities;
	EntityVector m_entities_to_add;
	EntityVector m_entities_to_remove;
	EntityMap m_entity_map;
	size_t m_entity_count = 0;

	// private method
	void removeDeadEntities(EntityVector& entity_vector)
	{
		for (auto& entity : m_entities_to_remove)
		{
			for (auto it = entity_vector.begin(); it != entity_vector.end(); it++)
			{
				if (entity->getId() == (*it)->getId())
				{
					// remove
					entity_vector.erase(it);
					break;
				}
			}
		}
	}

public:
	// constructor
	EntityManager() = default;

	// getter

	// setter

	// overload

	// other
	std::shared_ptr<Entity> addEntity(const std::string&);
	const EntityMap& getEntityMap();
	const EntityVector& getEntities();
	const EntityVector& getEntities(const std::string&);
	void update();
};
