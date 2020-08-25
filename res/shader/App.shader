#shader vertex
#version 330 core
layout(location = 0) in vec4 a_Position;

//layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in float a_TexIndex;

uniform mat4 u_MVP;

out vec2 v_TexCoord;
out float v_TexIndex;

void main()
{
	//gl_Position = u_MVP * vec4(a_Position,0.0f,0.0f);

	gl_Position = u_MVP * a_Position;

	v_TexCoord = a_TexCoord;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
}
#shader fragment
#version 330 core

layout(location = 0) out vec4 o_Color;

in vec2 v_TexCoord;
in float v_TexIndex;

uniform int u_Index[900];

uniform sampler2D u_Textures[10];



void main()
{
	int index = u_Index[int(v_TexIndex)];
	
	
	o_Color = texture(u_Textures[index], v_TexCoord);

}
