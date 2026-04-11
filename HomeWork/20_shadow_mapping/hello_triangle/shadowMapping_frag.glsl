#version 330 core
out vec4 FragColor;

in VS_OUT{
vec3 FragPos;
vec3 Normal;
vec2 TexCoords;
vec4 FragPosLightSpace;
}fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;


float ShadowCalculation(vec4 fragPosLightSpace){
//首先要执行透视的除法

vec3 projCoords = fragPosLightSpace.xyz/fragPosLightSpace.w;
projCoords = projCoords * 0.5 +0.5;//为了能和深度作比较，整个projCoords向量都必须换到0到1的范围内
float closestDepth =  texture(shadowMap,projCoords.xy).r;
float currentDepth = projCoords.z;

float bias = max(0.05 * (1.0 - dot(fs_in.Normal, normalize(lightPos - fs_in.FragPos))), 0.0005);



float shadow = 0.0;
vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
for(int x = -1; x <= 1; ++x)
{
    for(int y = -1; y <= 1; ++y)
    {
        float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
        shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
    }    
}
shadow /= 9.0;

if(projCoords.z>1.0){
shadow = 0.0;

}


return shadow;
//这个函数翻译过来的意思就是，如果你从光源点采样得到的深度，小于摄像机采样得到的深度
//那么就说明这个点处在阴影中 回1
}



void main(){
vec3 color = texture(diffuseTexture,fs_in.TexCoords).rgb;
vec3 normal = normalize(fs_in.Normal);
vec3 lightColor = vec3(1.0);
//下面是环境光
vec3 ambient = 0.15* lightColor;
//然后是漫反射
vec3 lightDir = normalize(lightPos - fs_in.FragPos);
float diff = max(dot(lightDir,normal),0.0);
vec3 diffuse = diff*lightColor;

//然后是镜面高光
vec3 viewDir = normalize(viewPos - fs_in.FragPos);
float spec = 0.0;
vec3 halfwayDir = normalize(lightDir +viewDir);
spec = pow(max(dot(normal,halfwayDir),0.0),64.0);
vec3 specular = spec * lightColor;


float shadow = ShadowCalculation(fs_in.FragPosLightSpace);  
vec3 lighting = (ambient  +(1.0 - shadow) * (diffuse +specular))*color;
FragColor = vec4(lighting,1.0);
//这里干的事情是：如果处在阴影中，那么漫反射和镜面高光就会归0
//只剩下一个环境光

}