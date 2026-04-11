#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec3 ourPos;
out vec2 TexCoord;

uniform float xOffset;

void main(){
gl_Position = vec4(-aPos.x+xOffset,aPos.y,aPos.z,1.0f);
ourPos  = aPos;
ourColor = aColor;
TexCoord = aTexCoord;
}