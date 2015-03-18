#pragma once

#include <GLRender/DataTypes.h>
#include <GLRender/Component/Component.h>

#include <vector>
#include <algorithm>

namespace glr
{
	typedef std::shared_ptr<Component> Component_Ptr;
	typedef std::vector<Component_Ptr> ComponentVector;
	
	class GLRENDERAPI Entity
	{
	public:
		typedef ComponentVector::size_type size_type;
		typedef ComponentVector::iterator iterator;
		typedef ComponentVector::const_iterator const_iterator;

		Entity(const string& name);

		const string& name() const;

		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;

		size_type size() const;

		template<class COMP_TYPE>
		std::shared_ptr<COMP_TYPE> addComponent();

		template<class COMP_TYPE>
		std::shared_ptr<COMP_TYPE> component();

		template<class COMP_TYPE>
		std::shared_ptr<const COMP_TYPE> component() const;

		template<class COMP_TYPE>
		bool getComponent(std::shared_ptr<COMP_TYPE>& ptr);

		template<class COMP_TYPE>
		bool getComponent(std::shared_ptr<const COMP_TYPE>& ptr) const;

	private:
		string m_name;

		ComponentVector m_components;
	};

	template<class COMP_TYPE>
	std::shared_ptr<COMP_TYPE> Entity::addComponent()
	{
		std::shared_ptr<COMP_TYPE> ptr(new COMP_TYPE);
		m_components.push_back(ptr);
		return ptr;
	}

	template<class COMP_TYPE>
	std::shared_ptr<COMP_TYPE> Entity::component()
	{
		std::shared_ptr<COMP_TYPE> ptr;
		std::find_if(begin(), end(),
			[&ptr](auto& c)
			{
				ptr = std::dynamic_pointer_cast<COMP_TYPE>(c); return bool(ptr);
			});
		return ptr;
	}

	template<class COMP_TYPE>
	std::shared_ptr<const COMP_TYPE> Entity::component() const
	{
		std::shared_ptr<const COMP_TYPE> ptr;
		std::find_if(begin(), end(),
			[&ptr](const auto& c)
			{
				ptr = std::dynamic_pointer_cast<const COMP_TYPE>(c); return bool(ptr);
			});
		return ptr;
	}

	template<class COMP_TYPE>
	bool Entity::getComponent(std::shared_ptr<COMP_TYPE>& ptr)
	{
		return std::find_if(begin(), end(),
			[&ptr](auto& c)
			{
				ptr = std::dynamic_pointer_cast<COMP_TYPE>(c); return bool(ptr);
			}) != end();
	}

	template<class COMP_TYPE>
	bool Entity::getComponent(std::shared_ptr<const COMP_TYPE>& ptr) const
	{
		return std::find_if(begin(), end(),
			[&ptr](const auto& c)
			{
				ptr = std::dynamic_pointer_cast<const COMP_TYPE>(c); return bool(ptr);
			}) != end();
	}
}