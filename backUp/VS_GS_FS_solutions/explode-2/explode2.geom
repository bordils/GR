#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vNormal[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;

const float speed = 1.2;
const float angSpeed = 8.0;
uniform float time;

void main( void )
{
	vec3 N = (vNormal[0]+vNormal[1]+vNormal[2])/3;
	float a = angSpeed*time;
	mat3 Rz=mat3(vec3(cos(a),  sin(a), 0),
              	 vec3(-sin(a), cos(a), 0), 
              	 vec3(0, 		0, 	  1));
    vec3 BT=(gl_in[0].gl_Position.xyz+gl_in[1].gl_Position.xyz+gl_in[2].gl_Position.xyz)/3; //Baricentre triangle
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		vec3 V=gl_in[i].gl_Position.xyz-BT;   // portar al centre
		V=Rz*V;                               // rotar sobre eix Z
		V+=BT+(speed*time*N);                              // traslladar al desti
		gl_Position=modelViewProjectionMatrix*vec4(V, 1);
		EmitVertex();
	}
    EndPrimitive();
}
