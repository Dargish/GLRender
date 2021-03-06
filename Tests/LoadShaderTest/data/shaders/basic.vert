#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 world;
uniform mat4 world_it;
out vec3 f_worldPos;
out vec3 f_normal;
out vec2 f_uv;
void main(void)
{
	vec4 worldPos = world * vec4(position, 1.0);
	f_worldPos = worldPos.xyz;
	f_normal = (world_it * vec4(normal, 0.0)).xyz;
	f_uv = uv;
	gl_Position = proj * view * worldPos;
}
