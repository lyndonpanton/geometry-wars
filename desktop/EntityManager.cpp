#include "EntityManager.h"

void EntityManager::update()
{
	for (auto& entity : m_entities_to_add)
	{
		m_entities.push_back(entity);
		m_entity_map[entity->getTag()].push_back(entity);
	}

	m_entities_to_add.clear();

	removeDeadEntities(m_entities);

	for (auto& [tag, entity_vector] : m_entity_map)
	{
		removeDeadEntities(entity_vector);
	}

	m_entities_to_remove.clear();
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	auto entity = std::shared_ptr<Entity>(new Entity(m_entity_count++, tag));

	m_entities_to_add.push_back(entity);

	if (m_entity_map.find(tag) == m_entity_map.end())
	{
		m_entity_map[tag] = EntityVector();
	}

	m_entity_map[tag].push_back(entity);

	return entity;
}

const EntityVector& EntityManager::getEntities()
{
	return m_entities;
}

const EntityVector& EntityManager::getEntities(const std::string& tag)
{
	return m_entity_map[tag];
}

const EntityMap& EntityManager::getEntityMap()
{
	return m_entity_map;
}
