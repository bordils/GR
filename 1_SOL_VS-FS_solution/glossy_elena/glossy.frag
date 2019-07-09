#version 330 core

uniform sampler2D glossy;
uniform int r=10;

in vec3 P;
in vec3 N;
out vec4 fragColor;

vec4 sampleTexture(sampler2D sampler, vec2 st, int r)
{
	vec4 col=vec4(0);
	for (int i=-r; i<=r;i++){
		for (int j=-r; j<=r;j++){
			col+=texture(sampler, vec2(st.s+(i/512),st.t+(j/512)));
		}
	}
	col/=pow(2*r+1,2);

	return col;
	//return col=texture(sampler,st);

}

vec4 sampleSphereMap(sampler2D sampler, vec3 R)
{
	float z = sqrt((R.z+1.0)/2.0);
	vec2 st = vec2((R.x/(2.0*z)+1.0)/2.0, (R.y/(2.0*z)+1.0)/2.0);
    st.y = -st.y;
	return sampleTexture(sampler, st, min(40,r));
}

void main()
{
	vec3 I = normalize(P);
	vec3 R = reflect(I, N);
	fragColor = sampleSphereMap(glossy, R);
}
