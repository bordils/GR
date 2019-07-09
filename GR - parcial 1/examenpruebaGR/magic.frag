#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
in vec3 normalE;
out vec4 fragColor;

uniform sampler2D window;
uniform sampler2D interior1;
uniform sampler2D exterior2;
void main()
{
	vec4 c = texture(window,vtexCoord);
	if(c.w == 1.0)
		fragColor = c;
	else
	{
		vec4 d = texture(interior1,vtexCoord + 0.5 * vec2(normalE.xy));
		if(d.w == 1.0)
			fragColor = d;
		else
			fragColor = texture(exterior2,vtexCoord + 0.7 * vec2(normalE.xy));
	}
    //fragColor = frontColor;
}
