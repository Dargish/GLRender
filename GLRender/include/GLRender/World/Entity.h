#pragma once

#include <GLRender/DataTypes.h>

#include <GLRender/Component/Component.h>

namespace glr
{
	class GLRENDERAPI Entity
	{
	public:
		Entity();
		Entity(const string& name);

		// Movable
		Entity(Entity&& o);
		Entity& operator=(Entity&& o);

		// Noncopyable
		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;

		const string& name() const;

		template<class T>
		std::shared_ptr<T> addComponent();

		template<class T>
		std::shared_ptr<T> component();

		template<class T>
		std::shared_ptr<const T> component() const;

		template<class T>
		bool getComponent(std::shared_ptr<T> comp);

		template<class T>
		bool getComponent(std::shared_ptr<const T> comp) const;

		template<class T>
		ComponentVector components();

	private:
		string m_name;

		ComponentVector m_components;
	};

	template<class T>
	std::shared_ptr<T> Entity::addComponent()
	{
		std::shared_ptr<T> ptr(new T);
		m_components.push_back(ptr);
		return ptr;
	}

	template<class T>
	std::shared_ptr<T> Entity::component()
	{
		ComponentVector::iterator it = m_components.begin();
		for (; it != m_components.end(); ++it)
		{
			std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(*it);
			if (ptr)
			{
				return ptr;
			}
		}
		return std::shared_ptr<T>();
	}

	template<class T>
	std::shared_ptr<const T> Entity::component() const
	{
		ComponentVector::const_iterator it = m_components.begin();
		for (; it != m_components.end(); ++it)
		{
			std::shared_ptr<const T> ptr = std::dynamic_pointer_cast<const T>(*it);
			if (ptr)
			{
				return ptr;
			}
		}
		return std::shared_ptr<const T>();
	}

	template<class T>
	bool Entity::getComponent(std::shared_ptr<T> comp)
	{
		ComponentVector::iterator it = m_components.begin();
		for (; it != m_components.end(); ++it)
		{
			comp = std::dynamic_pointer_cast<T>(*it);
			if (comp)
			{
				return true;
			}
		}
		return false;
	}

	template<class T>
	bool Entity::getComponent(std::shared_ptr<const T> comp) const
	{
		ComponentVector::const_iterator it = m_components.begin();
		for (; it != m_components.end(); ++it)
		{
			comp = std::dynamic_pointer_cast<const T>(*it);
			if (comp)
			{
				return true;
			}
		}
		return false;
	}

	template<class T>
	ComponentVector Entity::components()
	{
		ComponentVector ret;
		ComponentVector::iterator it = m_components.begin();
		for (; it != m_components.end(); ++it)
		{
			std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(*it);
			if (ptr)
			{
				ret.push_back(ptr);
			}
		}
		return ret;
	}
}