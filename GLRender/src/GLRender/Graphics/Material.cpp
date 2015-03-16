#include <GLRender/Graphics/Material.h>

namespace glr
{
	Material::Material()
	{

	}

	Material::Material(const string& path)
	{
		load(path);
	}

	void Material::load(const string& path)
	{
		(void)path;
	}
}