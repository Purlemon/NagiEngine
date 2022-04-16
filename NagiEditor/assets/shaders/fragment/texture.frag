#version 330 core
			
layout(location = 0) out vec4 color;

uniform sampler2D u_Textures[32];

in vec2 v_TexCoord;
in vec4 v_Color;
flat in int v_TexIndex;
in float v_TilingFactor;

void main()
{
	color = texture(u_Textures[v_TexIndex], v_TexCoord * v_TilingFactor) * v_Color;
}
