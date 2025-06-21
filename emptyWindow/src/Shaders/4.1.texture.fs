#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in float ID;

uniform sampler2D texture1;

void main()
{
	if(abs(ID) < 0.5){
		FragColor = texture(texture1, vec2((TexCoord.x / 16) + 0, (TexCoord.y / 16) + 0));
	}
	else if(abs(ID - 1.0) < 0.5){
		FragColor = texture(texture1, vec2((TexCoord.x / 16) + 0.0625, (TexCoord.y / 16) + 0));
	}
	else if(abs(ID - 2.0) < 0.5){
		FragColor = texture(texture1, vec2((TexCoord.x / 16) + 0.0625 * 2, (TexCoord.y / 16) + 0));
	}
}