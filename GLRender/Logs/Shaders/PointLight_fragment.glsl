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


in vec3 f_eyePos;
in vec3 f_worldPos;
uniform vec2 screenSize;
uniform vec3 lightPosition;
uniform vec3 color;
uniform float intensity;
out vec4 fragColor;
void main(void)
{
	vec2 uv = gl_FragCoord.xy / screenSize;
	GBufferData data = ReadGBuffer(uv);

	vec3 eyeVec = normalize(f_worldPos - f_eyePos);

	vec3 worldPos = f_eyePos + (normalize(eyeVec) * data.Depth);
	float distanceFromLight = distance(lightPosition, worldPos);

	float a = 0.00025;
	float b = 10.0;
	float d2 = distanceFromLight * distanceFromLight;
	float attenuatedIntensity = ((intensity + a) / (1 + b * d2)) - a;

	vec3 V = normalize(-eyeVec);
	vec3 L = normalize(lightPosition - worldPos);
	vec3 H = normalize(V + L);

	float VoL = saturate(dot(V, L));
	float NoV = saturate(dot(data.Normal, V));
	float VoH = saturate(dot(V, H));
	float NoH = saturate(dot(data.Normal, H));
	float NoL = saturate(dot(data.Normal, L));
	float LoH = saturate(dot(L, H));

	vec3 DiffuseColor = data.Color - data.Color * data.Metallicity;
	vec3 f0 = mix( vec3(0.04), data.Color, data.Metallicity );

	vec3 F = F_Schlick(f0, LoH);
	float G = Vis_Schlick(data.Roughness, NoV, NoL);
	float D = D_GGX(data.Roughness, NoH);

	vec3 specular = (F * G * D) * NoL;// / (4*NoL*NoV);
	vec3 diffuse = Diffuse_OrenNayar(DiffuseColor, data.Roughness, VoL, NoV, NoL, VoH);

	vec3 preGamma = (diffuse + specular) * attenuatedIntensity * color;
	vec3 postGamma = gammaCorrect(preGamma);
	fragColor = vec4(postGamma, 1);
	//fragColor = vec4(attenuatedIntensity, attenuatedIntensity, attenuatedIntensity, 1);
	//fragColor = vec4(0);
	//fragColor = vec4(NoL * specular * intensity, 1);
	//fragColor = vec4(diffuse * intensity, 1);
	//fragColor = vec4(F, 1);
	//fragColor = vec4(NoL * specular * intensity * color, 1);
	//fragColor = vec4(NoL * diffuse * intensity * color, 1);
	//fragColor = vec4(vec3(D * 0.01) * intensity, 1);
}
