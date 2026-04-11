#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1)in vec3 aNormal;//这里放法线
layout(location = 2) in vec2 aTextCoords;


uniform mat4 lightSpaceMatrix;
uniform mat4 model;



void main()
{


gl_Position = lightSpaceMatrix * model * vec4(aPos,1.0);

}
