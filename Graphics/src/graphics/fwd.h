#pragma once
#include <core/fwd.h>

namespace graphics
{
	DECL_CLASS(Camera);
	DECL_CLASS(RGBABuffer);
	DECL_CLASS(FrameBuffer);
	DECL_CLASS(GLBuffer);
	DECL_CLASS(IndexBuffer);
	DECL_CLASS(Material);
	DECL_CLASS(Mesh);
	DECL_CLASS(Model);
	DECL_CLASS(ShaderValue);
	DECL_CLASS(Shader);
	DECL_CLASS(Texture);
	DECL_CLASS(TextureBuffer);
	DECL_CLASS(TextureData);
	DECL_CLASS(TextureFile);
	DECL_CLASS(Transform);
	DECL_CLASS(Vertex);
	DECL_CLASS(VertexBuffer);
	DECL_CLASS(Window);

	namespace lights
	{
		DECL_CLASS(DirectionalLight);
		DECL_CLASS(Light);
	}
	namespace loaders
	{
		DECL_CLASS(AssimpModelLoader);
		DECL_CLASS(ModelLoader);
	}
	namespace primitives
	{
		DECL_CLASS(Cube);
		DECL_CLASS(Plane);
		DECL_CLASS(Sphere);
		DECL_CLASS(Torus);
	}
}