#version 400



in vec3 f_normal;
in float f_depth;
uniform vec3 v_color = vec3(1.0,1.0,1.0);
uniform float v_roughness = float(1.0);
uniform float v_metallicity = float(1.0);
layout (location = 0) out vec4 g_color;
layout (location = 1) out vec4 g_normal;
layout (location = 2) out vec4 g_depth;
void main(void)
{
	g_color = vec4(v_color, v_roughness);
	g_normal = vec4(f_normal, v_metallicity);
	g_depth = vec4(f_depth, 0, 0, 0);
}
