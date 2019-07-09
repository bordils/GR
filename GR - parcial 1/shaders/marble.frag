#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 normalM;
in vec3 vertexM;

in vec3 normalE;
in vec3 vertexE;

uniform sampler2D noise;

vec4 S = 0.3 * vec4(0,1,-1,0);
vec4 T = 0.3 * vec4(-2,-1,1,0);

float s = S.x*vertexM.x + S.y*vertexM.y + S.z*vertexM.z + S.w;
float t = T.x*vertexM.x + T.y*vertexM.y + T.z*vertexM.z + T.w;

float v,noiseR;

vec4 white = vec4(1,1,1,1);
vec4 redish = vec4(0.5,0.2,0.2,1.0);
vec4 diffuse;

vec4 shading(vec3 N, vec3 Pos, vec4 diffuse)
{
	vec3 lightPos = vec3(0.0,0.0,2.0);
	vec3 L = normalize( lightPos - Pos );
	vec3 V = normalize( -Pos);
	vec3 R = reflect(-L,N);
	float NdotL = max( 0.0, dot( N,L ) );
	float RdotV = max( 0.0, dot( R,V ) );
	float Ispec = pow( RdotV, 20.0 );
	return diffuse * NdotL + Ispec;
}

void main()
{
	noiseR = 2 * texture(noise,vec2(s,t)).x;
	if(floor(noiseR) == 0.0)
		diffuse = mix(white,redish,fract(noiseR));
	else if(floor(noiseR) == 1)
		diffuse = mix(redish,white,fract(noiseR));

    fragColor = shading(normalE,vertexE,diffuse);
}
