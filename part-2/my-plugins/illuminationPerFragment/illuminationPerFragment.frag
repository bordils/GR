#version 330 core

in vec3 fragPos;
in vec3 normalV;

in vec4 frontColor;
out vec4 fragColor;

uniform mat4 viewMatrix;

uniform vec4 matAmbient;    // Ka
uniform vec4 matDiffuse;    // Kd
uniform vec4 matSpecular;   // Ks
uniform float matShininess; // s

uniform vec4 lightAmbient;  // Ia
uniform vec4 lightDiffuse;  // Id
uniform vec4 lightSpecular; // Is
uniform vec4 lightPosition; // vector L, always in Eye Space

void main()
{   
    vec3 L = normalize(lightPosition.xyz - fragPos);
    vec3 R = normalize(2.0 * dot(normalV, L) * normalV - L);
    // alternative: vec3 R = reflect(-L, normalV);
    vec3 V = normalize(-fragPos);

    vec4 Ka = matAmbient;
    vec4 Kd = matDiffuse;
    vec4 Ks = matSpecular;
    float s = matShininess;

    vec4 Ia = lightAmbient;
    vec4 Id = lightDiffuse;
    vec4 Is = lightSpecular;

    fragColor = Ka*Ia + Kd*Id*max(0.0, dot(normalV, L)) + Ks*Is*pow(max(0.0, dot(R, V)), s);
    // light = ambient + diffuse (does not take into account the viewer pos) + specular (takes into account the viewer pos)
}
