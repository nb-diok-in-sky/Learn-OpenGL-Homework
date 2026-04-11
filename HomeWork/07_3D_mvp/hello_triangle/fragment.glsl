#version 330 core
out vec4 FragColor;
in vec3 ourPos;
in vec2 TexCoord;


uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform int texIndex;//这个用来整一整切换渲染的
uniform float terp ;
void main(){

if(texIndex == 0){
FragColor = mix(texture(texture1,TexCoord),texture(texture2,TexCoord),terp);
}else{
FragColor = texture(texture3,TexCoord);
}
} 