#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec3 ourPos;
out vec2 TexCoord;

uniform float xOffset;
uniform mat4 transform;

void main(){
gl_Position = transform * vec4(aPos,1.0f);
ourPos  = aPos;
ourColor = aColor;
TexCoord = vec2(aTexCoord.x,aTexCoord.y);



}