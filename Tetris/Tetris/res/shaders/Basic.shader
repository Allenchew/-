#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 owncolor;

out vec4 outcolor;
out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
	outcolor = owncolor;
	gl_Position = u_MVP * position;
	v_TexCoord = texCoord;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 outcolor;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color =texColor*outcolor;
};


