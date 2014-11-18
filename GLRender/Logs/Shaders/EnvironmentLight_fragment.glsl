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
uniform samplerCube cubeMap;
uniform float intensity;
out vec4 fragColor;
void main(void)
{
	GBufferData data = ReadGBuffer(f_uv);

	vec3 V = normalize(-f_eyeVec);
	vec3 diffL = data.Normal;
	vec3 specL = reflect(-V, data.Normal);
	vec3 diffH = normalize(V + diffL);
	vec3 specH = normalize(V + specL);

	vec3 diffuseLightColor = textureLod(cubeMap, diffL, 10.0).rgb;
	vec3 specularLightColor = textureLod(cubeMap, specL, data.Roughness * 10.0).rgb;

	float NoV = saturate(dot(data.Normal, V));

	vec3 DiffuseColor = data.Color - data.Color * data.Metallicity;
	vec3 f0 = mix( vec3(0.04), data.Color, data.Metallicity );

	float specLoH = saturate(dot(specL, specH));
	float specNoL = saturate(dot(data.Normal, specL));
	float specNoH = 1.0;
	//vec3 F = F_Schlick(f0, specLoH);
	//float G = Vis_Schlick(data.Roughness, NoV, specNoL);
	//float D = D_Beckmann(data.Roughness, specNoH);

	//vec3 specular = (F * G * D);
	vec3 specular = F_Schlick(f0, specLoH) * (1.0 - data.Roughness);

	float diffVoL = saturate(dot(V, diffL));
	float diffVoH = saturate(dot(V, diffH));
	vec3 diffuse = Diffuse_OrenNayar(DiffuseColor, data.Roughness, diffVoL, NoV, 1.0, diffVoH);

	vec3 preGamma = ((diffuse * diffuseLightColor) + (specular * specularLightColor)) * intensity;
	vec3 postGamma = gammaCorrect(preGamma);
	fragColor = vec4(postGamma, 1);
	//fragColor = vec4(vec3(data.Roughness), 1);
	//fragColor = vec4(diffuse * diffuseLightColor, 1);
	//fragColor = vec4(vec3(D), 1);
}
