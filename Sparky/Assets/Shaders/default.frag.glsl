#version 460 core

out vec4 color;

in vec4 f_Color;
in vec2 f_TexCoord;

uniform sampler2D u_TexImage;
uniform sampler2D u_TexImage2;
uniform float u_MixValue;

void main()
{
	//color = f_Color;
	//color = texture(u_TexImage, vec2(f_TexCoord.x, f_TexCoord.y));
	//color = f_Color * texture(u_TexImage, f_TexCoord);
	//color = mix(texture(u_TexImage, f_TexCoord), texture(u_TexImage2, f_TexCoord), u_MixValue);
	color = f_Color * mix(texture(u_TexImage, f_TexCoord), texture(u_TexImage2, f_TexCoord), u_MixValue);
}