#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform sampler2D diffuseTexture;
uniform samplerCube depthMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float far_plane;
uniform bool shadows;


float ShadowCalculation(vec3 FragPos){
//首先要执行透视的除法

vec3 fragToLight = FragPos - lightPos;
float closestDepth = texture(depthMap, fragToLight).r;
closestDepth *= far_plane;
float currentDepth = length(fragToLight);
float bias = 0.05;
float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;


return shadow;
//这个函数翻译过来的意思就是，如果你从光源点采样得到的深度，小于摄像机采样得到的深度
//那么就说明这个点处在阴影中 回1
}



void main(){



vec3 color = texture(diffuseTexture,fs_in.TexCoords).rgb;
vec3 normal = normalize(fs_in.Normal);
vec3 lightColor = vec3(0.3);
//下面是环境光
vec3 ambient = 0.3* lightColor;
//然后是漫反射
vec3 lightDir = normalize(lightPos - fs_in.FragPos);
float diff = max(dot(lightDir,normal),0.0);
vec3 diffuse = diff*lightColor;

//然后是镜面高光
vec3 viewDir = normalize(viewPos - fs_in.FragPos);
vec3 reflectDir = reflect(-lightDir,normal);
float spec = 0.0;
vec3 halfwayDir = normalize(lightDir +viewDir);
spec = pow(max(dot(normal,halfwayDir),0.0),64.0);
vec3 specular = spec * lightColor;


float shadow = ShadowCalculation(fs_in.FragPos);  
vec3 lighting = (ambient  +(1.0 - shadow) * (diffuse +specular))*color;
FragColor = vec4(lighting,1.0);
//这里干的事情是：如果处在阴影中，那么漫反射和镜面高光就会归0
//只剩下一个环境光

}