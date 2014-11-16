#version 400



layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 world;
uniform mat4 world_it;
out vec2 f_uv;
out vec3 f_normal;
void main(void)
{
	f_uv = uv;
	f_normal = (world_it * vec4(normal, 0.0)).xyz;
	gl_Position = proj * view * world * vec4(position, 1.0);
}
