#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;


void paintVertex(bool x, bool y, vec4 v, vec4 col){
    gfrontColor=col;
    vec4 offset=vec4( x? 0.5:-0.5, y? 0.5:-0.5, 0, 0);
    gl_Position = v + offset;
    EmitVertex();
}

void main( void ){
    vec4 v0 = gl_in[0].gl_Position;
    vec4 v1 = gl_in[1].gl_Position;
    vec4 v2 = gl_in[2].gl_Position;
    vec4 col0 = vfrontColor[0];
    vec4 col1 = vfrontColor[1];
    vec4 col2 = vfrontColor[2];
    vec4 col3 = vfrontColor[3];
    
    v0 = v0/v0.w;
    v1 = v1/v1.w;
    v2 = v2/v2.w;
    // Tot en NDC
    paintVertex(true, true, v0, col0);
    paintVertex(true, true, v1, col1);
    paintVertex(true, true, v2, col2);
    EndPrimitive();
    paintVertex(true, false, v0, col0);
    paintVertex(true, false, v1, col1);
    paintVertex(true, false, v2, col2);
    EndPrimitive();
    paintVertex(false, true, v0, col0);
    paintVertex(false, true, v1, col1);
    paintVertex(false, true, v2, col2);
    EndPrimitive();
    paintVertex(false, false, v0, col0);
    paintVertex(false, false, v1, col1);
    paintVertex(false, false, v2, col2);
    EndPrimitive();
}
