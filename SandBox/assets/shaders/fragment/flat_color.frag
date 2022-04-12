#version 330 core
			
layout(location = 0) out vec4 color;

uniform vec4 u_Color;

in vec3 v_Position;

void main()
{
	color = u_Color;
	//color = vec4(0.5f,0.5f,0.5f,1.0f);
}