#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in int a_TexIndex;
layout(location = 4) in float a_TilingFactor;

uniform mat4 u_ProjectionView;
uniform mat4 u_Transform;

out vec2 v_TexCoord;
out vec4 v_Color;
flat out int v_TexIndex;	// 着色器之间不能传int,因为无法插值,需要用flat声明不插值
out float v_TilingFactor;

void main()
{
	v_TexCoord = a_TexCoord;
	v_Color=a_Color;
	v_TexIndex=a_TexIndex;
	v_TilingFactor=a_TilingFactor;
	//gl_Position = u_ProjectionView * u_Transform * vec4(a_Position, 1.0);	
	gl_Position = u_ProjectionView * vec4(a_Position, 1.0);	
}

		