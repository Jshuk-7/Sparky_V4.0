#version 460 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Color;
layout (location = 2) in vec2 a_TexCoord;

uniform mat4 u_Model = mat4(1.0);
uniform mat4 u_View = mat4(1.0);
uniform mat4 u_Proj = mat4(1.0);

out vec4 f_Color;
out vec2 f_TexCoord;

void main()
{
	gl_Position = u_Proj * u_View * u_Model * vec4(a_Pos, 1.0);
	f_Color = vec4(a_Color, 1.0);
	f_TexCoord = a_TexCoord;
}