#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform vec2 mouse;

void main()
{
    if (distance(gl_FragCoord.xy, mouse) > 100)
    {
        fragColor = frontColor;
        fragColor.a = 0.025;
    }
    else
    {
        fragColor = frontColor;
        fragColor.a = 0.25;
    }
}
