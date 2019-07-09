#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

out vec2 gtexCoord;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform float side = 0.1;

void quadVertex(int i, int j, int oi, int oj, vec3 V) {
    gtexCoord = vec2(i, j);
    float offset = side/2;
    vec3 aux = vec3(V.x+oi*offset, V.y+oj*offset, V.z);
    //vec3 aux = vec3(V.x-offset, V.y-offset, V.z);
    gl_Position = projectionMatrix*vec4(aux, 1);
    EmitVertex();
}

void paintQuad(vec4 V) {
    quadVertex(0, 0, -1, -1, V.xyz);
    quadVertex(1, 0, 1, -1, V.xyz);
    quadVertex(0, 1, -1, 1, V.xyz);
    quadVertex(1, 1, 1, 1, V.xyz);
    EndPrimitive();
}

void main( void )
{
	paintQuad(modelViewMatrix*gl_in[0].gl_Position);
}
