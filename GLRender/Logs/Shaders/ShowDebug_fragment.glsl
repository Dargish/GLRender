#version 400
uniform float PI = 3.14159265359;

struct GBufferData
{
	vec3 Color;
	vec3 Normal;
	float Roughness;
	float Metallicity;
	float Depth;
};


uniform sampler2D g_A;
uniform sampler2D g_B;
uniform sampler2D g_C;
GBufferData ReadGBuffer(
	vec2 uv)
{
	GBufferData data;
	vec4 A = texture(g_A, uv);
	vec4 B = texture(g_B, uv);
	vec4 C = texture(g_C, uv);
	data.Color = A.rgb;
	data.Roughness = A.a;
	data.Normal = normalize(B.rgb);
	data.Metallicity = B.a;
	data.Depth = C.r;
	return data;
}

float saturate(
	float v)
{
	return clamp(v, 0.0, 1.0);
}

vec3 saturate(
	vec3 v)
{
	return clamp(v, vec3(0.0), vec3(1.0));
}

vec3 gammaCorrect(
	vec3 preGamma)
{
	return pow(preGamma, vec3(1.0/2.2));
}

float gammaCorrect(
	float preGamma)
{
	return pow(preGamma, (1.0/2.2) );
}

vec3 Diffuse_OrenNayar(
	vec3 DiffuseColor,
	float Roughness,
	float VoL,
	float NoV,
	float NoL,
	float VoH)
{
	float m = Roughness * Roughness;
	float m2 = m * m;
	float C1 = 1 - 0.5 * m2 / (m2 + 0.33);
	float Cosri = VoL - NoV * NoL;
	float C2 = 0.45 * m2 / (m2 + 0.09) * Cosri * ( Cosri >= 0 ? min( 1, NoL / NoV ) : NoL );
	return DiffuseColor / PI * ( NoL * C1 + C2 );
}

float D_GGX(
	float Roughness,
	float NoH)
{
	float m = Roughness * Roughness;
	float m2 = m * m;
	float d = ( NoH * m2 - NoH ) * NoH + 1;
	return m2 / ( PI*d*d );
}

float D_Beckmann(
	float Roughness,
	float NoH)
{
	float m = Roughness * Roughness;
	float m2 = m * m;
	float NoH2 = NoH * NoH;
	return exp( (NoH2 - 1) / (m2 * NoH2) ) / ( PI * m2 * NoH2 * NoH2 );
}

float Vis_Schlick(
	float Roughness,
	float NoV,
	float NoL)
{
	float k = ( Roughness * Roughness ) * 0.5;
	float Vis_SchlickV = NoV * (1 - k) + k;
	float Vis_SchlickL = NoL * (1 - k) + k;
	return 0.25 / ( Vis_SchlickV * Vis_SchlickL );
}

float Vis_Smith(
	float Roughness,
	float NoV,
	float NoL)
{
	float a = ( Roughness * Roughness );
	float a2 = a*a;

	float Vis_SmithV = NoV + sqrt( NoV * (NoV - NoV * a2) + a2 );
	float Vis_SmithL = NoL + sqrt( NoL * (NoL - NoL * a2) + a2 );
	return inversesqrt( Vis_SmithV * Vis_SmithL );
}

vec3 F_Schlick(
	vec3 f0,
	float LoH)
{
	// Anything less than 2% is physically impossible and is instead considered to be shadowing
	//return SpecularColor + ( saturate( 50.0 * SpecularColor.g ) - SpecularColor ) * exp2( (-5.55473 * VoH - 6.98316) * VoH );
	//return mix(SpecularColor, vec3(1.0), pow(1.0 - VoH, 5));
	return f0 + (vec3(1.0) - f0) * pow((1.0 - LoH), 5);
}


in vec2 f_uv;
in vec3 f_eyeVec;
uniform float drawColor;
uniform float drawNormal;
uniform float drawRoughness;
uniform float drawMetallicity;
uniform float drawDepth;
uniform vec3 direction;
uniform vec3 color;
uniform float intensity;
out vec4 fragColor;
void main(void)
{
	GBufferData data = ReadGBuffer(f_uv);
	vec3 color = data.Color * drawColor;
	color += data.Normal * drawNormal;
	color += data.Roughness * drawRoughness;
	color += data.Metallicity * drawMetallicity;
	color += data.Depth * drawDepth * 0.01; // to make distance viewable
	fragColor = vec4(color, 1);
}
