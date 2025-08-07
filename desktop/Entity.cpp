#include "Entity.h"

bool Entity::getIsActive() const
{
	return m_is_active;
}

size_t Entity::getId() const
{
	return m_id;
}

const std::string& Entity::getTag() const
{
	return m_tag;
}

template <typename T>
T& Entity::get()
{
	return std::get<T>(m_components);
}

template <typename T>
const T& Entity::get() const
{
	return std::get<T>(m_components);
}

void Entity::destroy()
{
	m_is_active = false;
}

template <typename T, typename... TArgs>
T& Entity::add(TArgs&&... m_args)
{
	auto& component = get<T>();
	component = T(std::forward<TArgs>(m_args));
	component.exists = true;

	return component;
}

template <typename T>
bool Entity::has() const
{
	return get<T>().exists;
}

template <typename T>
void Entity::remove()
{
	get<T>() = T();
}
