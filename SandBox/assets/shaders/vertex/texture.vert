#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_ProjectionView;
uniform mat4 u_Transform;

out vec2 v_TexCoord;
out vec4 v_Color;

void main()
{
	v_TexCoord = a_TexCoord;
	v_Color=a_Color;
	//gl_Position = u_ProjectionView * u_Transform * vec4(a_Position, 1.0);	
	gl_Position = u_ProjectionView * vec4(a_Position, 1.0);	
}

		