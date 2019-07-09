in vec3 N;   
in vec3 P;
out vec4 fragColor;

uniform mat4 modelViewMatrix;

uniform vec4 lightAmbient;
uniform vec4 lightSpecular;

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

vec4 light(vec3 N, vec3 V, vec3 L, vec4 lightDiffuse)
{
  L = L-V;
  N=normalize(N); V=normalize(V); L=normalize(L);
  vec3 R = normalize( 2.0*dot(N,L)*N-L );
  float NdotL = max( 0.0, dot( N,L ) );
  float RdotV = max( 0.0, dot( R,V ) );
  float Idiff = NdotL;
  float Ispec = 0;
  if (NdotL>0) Ispec=pow( RdotV, matShininess );
  return matDiffuse  * lightDiffuse * Idiff+
    matSpecular * lightSpecular * Ispec;
}

void main()
{
	vec3 l1pos = (modelViewMatrix*vec4(1000,0,0,1)).xyz-P;
	vec4 l1diffuse = vec4(1,0,0,1); //red
	vec4 l1 = light(N,-P,l1pos,l1diffuse);
	
	vec3 l2pos = (modelViewMatrix*vec4(0,1000,0,1)).xyz-P;
	vec4 l2diffuse = vec4(0,1,0,1); //green
	vec4 l2 = light(N,-P,l2pos,l2diffuse);
	
	vec3 l3pos = (modelViewMatrix*vec4(0,0,1000,1)).xyz-P;
	vec4 l3diffuse = vec4(0,0,1,1); //blue
	vec4 l3 = light(N,-P,l3pos,l3diffuse);
    fragColor = l1+l2+l3;
}