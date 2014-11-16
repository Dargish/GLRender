#version 400



layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 binormal;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 world;
uniform mat4 world_it;
out vec2 f_uv;
out vec3 f_normal;
out vec3 f_tangent;
out vec3 f_binormal;
void main(void)
{
	f_uv = uv;
	f_normal = (world_it * vec4(normal, 0.0)).xyz;
	f_tangent = (world_it * vec4(tangent, 0.0)).xyz;
	f_binormal = (world_it * vec4(binormal, 0.0)).xyz;
	gl_Position = proj * view * world * vec4(position, 1.0);
}
