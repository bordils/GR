#version 330 core

in vec4 frontColor;
in vec3 N;
in vec3 P;

out vec4 fragColor;

in vec3 redLightPos;
in vec3 greenLightPos;
in vec3 blueLightPos;

uniform vec4 matDiffuse; //Kd
uniform vec4 matSpecular; //Ks
uniform vec4 lightSpecular;//ls
uniform float matShininess; //s


vec4 light(vec3 V, vec3 N, vec3 P, vec3 lightPos,vec4 lightColor)
{
	//N = normalize(N);
	vec3 L = normalize(lightPos);
	vec3 R = reflect(-L,N);
	float NdotL = max(0.0,dot(N,L));
	float RdotV = max(0.0,dot(R,V));
	float spec = pow(RdotV,matShininess);
	return vec4(matDiffuse * lightColor * NdotL + matSpecular * lightSpecular * spec);
}
void main()
{
	vec3 V = normalize(-P);
	vec4 l1 = light(V,N,P,redLightPos,vec4(1,0,0,1));
	vec4 l2 = light(V,N,P,greenLightPos,vec4(0,1,0,1));
	vec4 l3 = light(V,N,P,blueLightPos,vec4(0,0,1,1));
	
    fragColor =(l1 + l2 + l3) * frontColor;
}
