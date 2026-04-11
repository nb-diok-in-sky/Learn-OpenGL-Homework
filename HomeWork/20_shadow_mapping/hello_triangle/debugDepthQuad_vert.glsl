#version 330 core
layout(location = 0) in vec3 aPos;//这里需要in 一下顶点坐标  法线 纹理坐标 
layout(location = 1)in vec3 aNormal;//这里放法线
layout(location = 2) in vec2 aTextCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TextCoords;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TextCoords = aTextCoords;
}