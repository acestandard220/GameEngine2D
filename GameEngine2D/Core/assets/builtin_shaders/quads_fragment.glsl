#version 330 core

out vec4 FragColor;

uniform vec3 color;
uniform sampler2D diffuse_texture;

uniform int textured;

in vec2 TexC;

void main(){

    if(textured==1)
	{
	    texture(diffuse_texture,TexC);
	}
	else
	{
	    FragColor = vec4(color,1.0f);
	}
}

