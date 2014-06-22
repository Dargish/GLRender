#pragma once
#include "fwd.h"
#include <vector>

namespace ecs
{
	class Entity
	{
	public:
		Entity();
		~Entity();

		void serialise(Json::Value& entityArray) const;
		void deserialise(const Json::Value& componentArray);

		template<class T>
		boost::shared_ptr<T> createComponent()
		{
			boost::shared_ptr<T> component(new T);
			m_components.push_back(component);
			return component;
		}

		template< class COMPONENT_TYPE >
		bool getComponent(boost::shared_ptr< COMPONENT_TYPE >& component)
		{
			std::vector< EntityComponent_Ptr >::iterator it = m_components.begin();
			for (; it != m_components.end(); ++it)
			{
				boost::shared_ptr< COMPONENT_TYPE > typedComp = boost::dynamic_pointer_cast<COMPONENT_TYPE>(*it);
				if (typedComp.get())
				{
					component = typedComp;
					return true;
				}
			}
			return false;
		}

		template< class COMPONENT_TYPE >
		bool getComponent(boost::shared_ptr< const COMPONENT_TYPE >& component) const
		{
			std::vector< EntityComponent_Ptr >::const_iterator it = m_components.begin();
			for (; it != m_components.end(); ++it)
			{
				boost::shared_ptr< const COMPONENT_TYPE > typedComp = boost::dynamic_pointer_cast<const COMPONENT_TYPE>(*it);
				if (typedComp.get())
				{
					component = typedComp;
					return true;
				}
			}
			return false;
		}

		template< class COMPONENT_TYPE >
		size_t getComponents(std::vector<boost::shared_ptr< COMPONENT_TYPE >>& components)
		{
			std::vector< EntityComponent_Ptr >::iterator it = m_components.begin();
			for (; it != m_components.end(); ++it)
			{
				boost::shared_ptr< COMPONENT_TYPE > typedComp = boost::dynamic_pointer_cast<COMPONENT_TYPE>(*it);
				if (typedComp.get())
				{
					components.push_back(typedComp);
				}
			}
			return components.size();
		}

		template< class COMPONENT_TYPE >
		size_t getComponents(std::vector<boost::shared_ptr< const COMPONENT_TYPE >>& components) const
		{
			std::vector< EntityComponent_Ptr >::const_iterator it = m_components.begin();
			for (; it != m_components.end(); ++it)
			{
				boost::shared_ptr< const COMPONENT_TYPE > typedComp = boost::dynamic_pointer_cast<const COMPONENT_TYPE>(*it);
				if (typedComp.get())
				{
					components.push_back(typedComp);
				}
			}
			return components.size();
		}

		const std::vector< EntityComponent_Ptr >& components() const;

	private:
		std::vector< EntityComponent_Ptr > m_components;
	};
}
