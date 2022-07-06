#version 460 core

out vec4 color;

in vec4 f_Color;
in vec2 f_TexCoord;

uniform sampler2D u_TexImage;

void main()
{
	//color = f_Color;
	//color = texture(u_TexImage, vec2(f_TexCoord.x, f_TexCoord.y));
	color = f_Color * texture(u_TexImage, f_TexCoord);
}