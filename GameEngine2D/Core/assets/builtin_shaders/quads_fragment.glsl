#version 330 core

out vec4 FragColor;

uniform vec3 color;

in vec2 TexC;

void main(){
	FragColor = vec4(color,1.0f);
}

