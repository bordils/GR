#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec3 vertexE;
void main()
{
	vec3 st = dFdx(vertexE);
	vec3 nd = dFdy(vertexE);
	vec3 rd = cross(st,nd);
    fragColor = frontColor * normalize(rd).z;
}
