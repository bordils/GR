#version 330 core

in vec4 frontColor;
in vec3 N;
in vec3 P;
out vec4 fragColor;

void main()
{
	//x face
	float xFace = floor((dot(N,vec3(1,0,0)) + 0.5));
	float yFace = floor((dot(N,vec3(0,1,0)) + 0.5));
	float zFace = floor((dot(N,vec3(0,0,1)) + 0.5));
	if(xFace == 1.0 || xFace == -1.0)
	{
		vec2 q = vec2(P.y,P.z);
		if(distance(q,vec2(0)) < 0.2)
			fragColor = vec4(0);
		else
    			fragColor = frontColor;
	}	
	else if(yFace == 1.0 || yFace == -1.0)
	{
		vec2 q = vec2(P.x,P.z);
		if(distance(q,vec2(0.5)) < 0.2 || distance(q,vec2(-0.5)) < 0.2)
			fragColor = vec4(0);
		else
    			fragColor = frontColor;
	}
	else if(zFace == 1.0 || zFace == -1.0)
	{
		vec2 q = vec2(P.x,P.y);
		if(distance(q,vec2(0.5)) < 0.2 || distance(q,vec2(-0.5)) < 0.2 || distance(q,vec2(0)) < 0.2)
			fragColor = vec4(0);
		else
    			fragColor = frontColor;
	}
	else
		fragColor = frontColor;
}
