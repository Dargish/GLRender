#include <GLRender/DataTypes.h>

namespace glr
{
	class GLRENDERAPI Entity
	{
	public:
		Entity(const string& name);

		bool operator==(const Entity& other) const;

		const string& name() const;

	private:
		Entity(const Entity& other) = delete;
		Entity& operator=(const Entity&) = delete;

		string m_name;
	};
}