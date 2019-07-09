#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float disp = 0.05;

const vec4 WHITE = vec4(vec3(1.0), 1);

void triangleVertex(vec3 V, vec3 N, vec4 color) 
{
    gfrontColor = color;
    gl_Position = modelViewProjectionMatrix*vec4(V, 1);
    EmitVertex();
}

vec3 getNormal(vec3 A, vec3 B, vec3 C)
{
    vec3 u = B-A;
    vec3 v = C-A;
    return normalize(cross(u, v));
}

void paintTriangles() 
{
    vec3 V0 = gl_in[0].gl_Position.xyz;
    vec3 V1 = gl_in[1].gl_Position.xyz;
    vec3 V2 = gl_in[2].gl_Position.xyz;
    vec3 BT = (V0 + V1 + V2)/3;
    vec3 N = getNormal(V0, V1, V2);
    BT += N*disp;    

    // Triangle1
    N = normalMatrix*getNormal(V0, BT, V1);
    triangleVertex(V0, N, vfrontColor[0]*N.z);
    triangleVertex(BT, N, WHITE);
    triangleVertex(V1, N, vfrontColor[1]*N.z);
    EndPrimitive();

    // Triangle2
    N = normalMatrix*getNormal(V2, V1, BT);
    triangleVertex(V2, N, vfrontColor[2]*N.z);
    triangleVertex(V1, N, vfrontColor[1]*N.z);
    triangleVertex(BT, N, WHITE);
    EndPrimitive();

    // Triangle3
    N = normalMatrix*getNormal(V0, V2, BT);
    triangleVertex(V0, N, vfrontColor[0]*N.z);
    triangleVertex(V2, N, vfrontColor[2]*N.z);
    triangleVertex(BT, N, WHITE);
    EndPrimitive();
}

void main( void )
{
	paintTriangles();
}
