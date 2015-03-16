#include <GLRender/Game.h>
#include <GLRender/World/World.h>
#include <GLRender/Renderer/ForwardRenderer.h>
#include <GLRender/Graphics/Shader.h>
#include <GLRender/Graphics/Model.h>
#include <GLRender/Component/ModelComponent.h>
#include <GLRender/Component/TransformComponent.h>
#include <GLRender/Component/MaterialComponent.h>

using namespace glr;

int main()
{
	Game game;

	game.showWindow(1280, 720, "Pioneer");

	World& world = game.world();

	world.addModel("cerberus", "data/models/cerberus.fbx");

	//Entity& model = world.createEntity("test");
	//model.addComponent<TransformComponent>();
	//model.addComponent<MaterialComponent>();
	//std::shared_ptr<ModelComponent> modelComponent = model.addComponent<ModelComponent>();

	//Model::MeshType mesh;
	//Model::MeshType::VertexBuffer& vertexBuffer = mesh.vertexBuffer();
	//IndexBuffer& indexBuffer = mesh.indexBuffer();
	//vertexBuffer.resize(3);
	//vertexBuffer[0].position = Vector3(0, 1, 0);
	//vertexBuffer[1].position = Vector3(0, 0, 0);
	//vertexBuffer[2].position = Vector3(1, 0, 1);
	//indexBuffer.resize(3);
	//indexBuffer[0] = 0;
	//indexBuffer[1] = 2;
	//indexBuffer[2] = 1;
	//modelComponent->model.addMesh(mesh);

	/*std::shared_ptr<ForwardRenderSystem> renderSystem = */game.setRenderer<ForwardRenderer>();

	return game.run();
}