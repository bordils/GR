#version 330 core

uniform bool world ;
uniform mat4 modelViewMatrixInverse;

out vec4 fragColor;

in vec3 N;
in vec3 P;

uniform float time;
uniform bool rotate = true;

uniform mat4 viewMatrixInverse;

vec4 light1Pos = vec4(0,10,0,0.0);
vec4 light2Pos = vec4(0,-10,0,0.0);
vec4 light3Pos = vec4(10,0,0,0.0);
vec4 light4Pos = vec4(-10,0,0,0.0);
// V, N, P, lightPos must be in the same coordinate space
// V is the unit vector towards the observer
// N is normal
// P is the position
// lightPos is the position of light
// lightColor is the color of light
vec4 light(vec3 V, vec3 N, vec3 P, vec3 lightPos, vec3 lightColor)
{
	const float shininess = 100.0;
	const float Kd = 0.5;
	N = normalize(N);
	vec3 L = normalize(lightPos - P);
	vec3 R = reflect(-L, N);
	float NdotL = max(0.0, dot(N,L));
	float RdotV = max(0.0, dot(R,V));
	float spec =  pow( RdotV, shininess);
	return vec4(Kd*lightColor*NdotL + vec3(spec),0);
}

void main()
{
	float angle = 0;
	if (rotate) angle = time;
	float cs = cos(angle);
	float sn = sin(angle);
	mat3 R = mat3(vec3(cs, sn, 0), vec3(-sn, cs,0), vec3(0,0,1));

	
	vec3 V = normalize(/*modelViewMatrixInverse[3].xyz */-P);

	vec4 c,g,y,b,r = vec4(0);
	
	//c = light(V, N, P, R * vec3(0, 0, 0), vec3(1, 1, 1));
	
	g = light(V, N, P, R * (light1Pos).xyz, vec3(0,1,0));

	y = light(V, N, P, R * (light2Pos).xyz, vec3(1,1,0));

	b = light(V, N, P, R * (light3Pos).xyz, vec3(0,0,1));

	r = light(V, N, P, R * (light4Pos).xyz, vec3(1,0,0));

	fragColor = g + y + b + r;
}

