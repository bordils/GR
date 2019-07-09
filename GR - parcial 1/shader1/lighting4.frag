#version 330 core

in vec4 frontColor;
in vec3 normalF;
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

void main()
{
	vec3 L = normalize(lightPosition.xyz - fragPos);
	vec3 R = reflect(-L,normalF);
	vec3 V = normalize(-fragPos);

	vec4 ambient = lightAmbient * matAmbient;
	vec4 diffuse = lightDiffuse * matDiffuse * max(dot(normalF,L),0.0);
	vec4 specular = lightSpecular * matSpecular * pow(max(dot(R,V),0.0),matShininess);

    fragColor = ambient + diffuse + specular;
}
