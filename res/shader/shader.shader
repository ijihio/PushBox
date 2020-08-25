#shader vertex
#version 330 core
layout(location = 0) in vec4 aPos;
layout(location = 1) in vec2 aTexCoord;


out vec2 TexCoord;

void main()
{
	gl_Position = aPos;

	TexCoord = aTexCoord;
}
#shader fragment
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;


void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = texture(texture1, TexCoord);
	//FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
}

