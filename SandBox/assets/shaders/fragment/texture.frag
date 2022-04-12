#version 330 core
			
layout(location = 0) out vec4 color;

uniform sampler2D u_Texture;
uniform vec4 u_Color;
uniform float u_TilingFactor;

in vec2 v_TexCoord;

void main()
{
	color = texture(u_Texture, v_TexCoord * u_TilingFactor) * u_Color;
	//color = vec4(0.5f,0.5f,0.5f,1.0f);
}
