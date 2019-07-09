#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform float speed = 0.25;
uniform float time;

const float PI = 3.141592654;

void copyVertex(vec3 V, vec4 color)
{
    gfrontColor = color;
    gl_Position = modelViewProjectionMatrix*vec4(V, 1);
    EmitVertex(); 
}

void shrinkVertex(vec3 V, vec4 color, vec3 BT)
{
    float f = abs(sin(2*1.0*PI*fract(time*speed)));
    vec3 Mix = mix(V, BT, f);
    gfrontColor = color;
    gl_Position = modelViewProjectionMatrix*vec4(Mix, 1);
    EmitVertex();
}

void copy(vec3 V0, vec3 V1, vec3 V2)
{
    copyVertex(V0, vfrontColor[0]);
    copyVertex(V1, vfrontColor[1]);
    copyVertex(V2, vfrontColor[2]);
    EndPrimitive();
}

void shrink(vec3 V0, vec3 V1, vec3 V2)
{
    vec3 BT = (V0 + V1 + V2)/3;
    shrinkVertex(V0, vfrontColor[0], BT);
    shrinkVertex(V1, vfrontColor[1], BT);
    shrinkVertex(V2, vfrontColor[2], BT);
    EndPrimitive();
}
    

void main( void )
{
    vec3 V0 = gl_in[0].gl_Position.xyz;
    vec3 V1 = gl_in[1].gl_Position.xyz;
    vec3 V2 = gl_in[2].gl_Position.xyz;

    if (mod(time*speed, 2) < 1)
    {
        if (gl_PrimitiveIDIn%2 == 0) copy(V0, V1, V2);
        else shrink(V0, V1, V2);
    }
    else
    {
        if (gl_PrimitiveIDIn%2 == 0) shrink(V0, V1, V2);
        else copy(V0, V1, V2);
    }
}
        

    © 2018 GitHub, Inc.
    Terms
    Privacy
    Security
    Status
    Help

    Contact GitHub
    Pricing
    API
    Training
    Blog
    About

Press h to open a hovercard with more details.

