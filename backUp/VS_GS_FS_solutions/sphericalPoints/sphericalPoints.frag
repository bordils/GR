#version 330 core

in vec2 gtexCoord;
out vec4 fragColor;

uniform sampler2D sphere;

void main()
{
    vec4 TC = texture2D(sphere, gtexCoord);
    if (TC.a != 1.0) discard; 
    fragColor = TC;
}
