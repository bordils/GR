  #version 330 core

in vec3 normalF;
in vec3 fragPosMV;
in vec3 fragPos;

out vec4 fragColor;

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition;

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

uniform bool world = true;
uniform bool nomi;
uniform mat4 modelViewMatrixInverse;
uniform mat4 modelMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 viewMatrixInverse;
uniform mat3 normalMatrix;

vec3 L1,R1,V1,N1;

vec4 light(vec3 N, vec3 V, vec3 L)
{
	N=normalize(N); V=normalize(V); L=normalize(L);
	vec3 R = normalize( 2.0*dot(N,L)*N-L );
	float NdotL = max( 0.0, dot( N,L ) );
	float RdotV = max( 0.0, dot( R,V ) );
	float Idiff = NdotL;
	float Ispec = 0;
	if (NdotL>0) Ispec=pow( RdotV, matShininess );
	return
	matAmbient * lightAmbient +
	matDiffuse * lightDiffuse * Idiff+
	matSpecular * lightSpecular * Ispec;
}
void main()
{
	if(world)
	{
		L1 = normalize((viewMatrixInverse * lightPosition).xyz - fragPos);
		//R1 = reflect(-L1,normalF);
		V1 = normalize(modelViewMatrixInverse[3].xyz -fragPos); //the best way here should be to minus it from the camera position
		N1 = normalize(normalF);
	}
	else
	{
		L1 = normalize((/*modelViewMatrix */ lightPosition).xyz - fragPosMV);
		//R1 = reflect(-L1,normalF);
		V1 = normalize(-fragPosMV);
		N1 = normalize(normalMatrix * normalF);	
	}

    	fragColor = light(N1,V1,L1);
}

