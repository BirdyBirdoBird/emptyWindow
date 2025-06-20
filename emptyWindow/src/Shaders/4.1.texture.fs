#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in float ID;

uniform sampler2D texture1;

void main()
{
		//FragColor = texture(texture1, vec2((TexCoord.x / 16) + 0, (TexCoord.y / 16) + 0));
		FragColor = texture(texture1, vec2((TexCoord.x / 16) + 0.0625, (TexCoord.y / 16) + 0));
}