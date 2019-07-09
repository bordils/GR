#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform int mouseX;
uniform int mouseY;
uniform int height;

void main()
{

	vec2 fragPos= gl_FragCoord.xy;
	float mouseY2=abs(height-mouseY);
	float d= distance(fragPos, vec2(mouseX,mouseY2));

	vec4 color=frontColor;
	if (d>100)
	{
		color=vec4(color.xyz,0.025);
	}else{
		color=vec4(color.xyz,0.25);
	}
	fragColor= color;

}
