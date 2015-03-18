#version 400

in vec3 f_worldPos;
in vec3 f_normal;
in vec2 f_uv;
uniform sampler2D color;
uniform sampler2D roughness;
uniform sampler2D metallicity;
uniform vec3 eyePos;
// layout (location = 0) out vec4 g_color;
// layout (location = 1) out vec4 g_normal;
// layout (location = 2) out vec4 g_depth;
out vec4 fragColor;
void main(void)
{
	vec3 c = texture(color, f_uv).rgb;
	float r = texture(roughness, f_uv).r;
	float m = texture(metallicity, f_uv).r;

	float d = distance(f_worldPos, eyePos);

	// g_color = vec4(c, r);
	// g_normal = vec4(f_normal, m);
	// g_depth = vec4(d, 0.0, 0.0, 0.0);
	vec3 eye_dir = normalize(f_worldPos - eyePos);
	float col = dot(eye_dir, f_normal);
	fragColor = vec4(vec3(col * 0.5 + 0.5), 1.0);
	fragColor = vec4(f_worldPos, 1.0);
}
