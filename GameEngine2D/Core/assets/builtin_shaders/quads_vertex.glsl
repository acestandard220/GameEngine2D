#version 330 core
layout(location = 0) in vec3 aPos;
///layout (location = 1) in vec aNorm; ///GUIDE
layout(location = 2) in vec2 aTex;

uniform mat4 vp;
uniform mat4 model; //Also the transform

out vec2 TexC;
void main()
{
    gl_Position = vp * model * vec4(aPos,1.0f);
    TexC = aTex;
}
