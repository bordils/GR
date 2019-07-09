#version 330 core

out vec4 fragColor;

uniform sampler2D colorMap; // plane object: [0, 1]

in vec2 vtexCoord;

void main(){
    // Transform texture coords
    vec2 Q = vtexCoord*2; // [0, 2]
    Q = Q-vec2(1.0); // [-1, 1]

    // Q' calculations
    float r = length(Q);
    float r_prima = (r + 0.22*pow(r, 3) + 0.24*pow(r, 5));
    vec2 Q_prima = r_prima*normalize(Q);
    
    // Undo transformation
    vec2 tex = (Q_prima+vec2(1.0))/2.0;
    
    if(tex.x >= 0 && tex.x <= 1.0 && tex.y >= 0 && tex.y <= 1.0)
       fragColor = texture(colorMap, tex);
    else   
        fragColor = vec4(0);
}
