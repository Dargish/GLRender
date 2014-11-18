#version 400



in vec2 f_uv;
in vec3 f_normal;
in vec3 f_tangent;
in vec3 f_binormal;
in float f_depth;
uniform vec3 v_color = vec3(1.0,1.0,1.0);
uniform sampler2D t_color;
uniform sampler2D t_normal;
uniform float v_roughness = float(1.0);
uniform sampler2D t_roughness;
uniform float v_metallicity = float(1.0);
uniform sampler2D t_metallicity;
layout (location = 0) out vec4 g_color;
layout (location = 1) out vec4 g_normal;
layout (location = 2) out vec4 g_depth;
void main(void)
{
	mat3 TBN = mat3(f_tangent, f_binormal, f_normal);
	vec3 d = texture(t_color, f_uv).rgb * v_color;
	vec3 n = normalize(TBN * texture(t_normal, f_uv).rgb);
	float r = texture(t_roughness, f_uv).r * v_roughness;
	float m = texture(t_metallicity, f_uv).r * v_metallicity;

	g_color = vec4(d, r);
	g_normal = vec4(n, m);
	g_depth = vec4(f_depth, 0, 0, 0);
}
