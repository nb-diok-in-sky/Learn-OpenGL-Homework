#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

	
struct Material{
sampler2D diffuse;//漫反射光照  这个代表 我们期望物体本身的颜色
sampler2D specular;//镜面光照 镜面高光的颜色
float shininess;//反光度  高光的散射（半径）

};
//这里创建的是手电筒的结构体
struct Flashlight{
vec3 position;
vec3 direction;
vec3 ambient;
float cutOff;
float outerCutOff;
vec3 diffuse;
vec3 specular;

//这些是模拟衰减的
 float constant;
 float linear;
 float quadratic;

};


//这里是定向光
struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;




//下面放点光源
struct PointLight{
vec3 position;//位置
 float constant;
 float linear;
 float quadratic; //点光源衰减
     vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];//这里是定义了四个点光源




uniform sampler2D texture1;
 
uniform Flashlight flashlight;
uniform Material material;//材质名
uniform vec3 viewPos;//这个是摄像机的位置  也就是视角位置


vec3 CalcDirLight(DirLight dirlight, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-dirlight.direction);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);


    // 合并结果
    vec3 ambient  = dirlight.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = dirlight.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = dirlight.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}




vec3 CalcPointLight(PointLight pointlight, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(pointlight.position - fragPos);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 衰减
    float distance    = length(pointlight.position - fragPos);
    float attenuation = 1.0 / (pointlight.constant + pointlight.linear * distance + 
                 pointlight.quadratic * (distance * distance));    
    // 合并结果
    vec3 ambient  =  pointlight.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  =  pointlight.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular =  pointlight.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}//点光源的函数






void main(){


	//漫反射光照
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(flashlight.position - FragPos );
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse =diff * flashlight.diffuse*vec3(texture(material.diffuse,TexCoords));
	vec3 ambient = flashlight.ambient * vec3(texture(material.diffuse,TexCoords));


	//接下来是镜面光照
	vec3 viewDir = normalize(viewPos - FragPos);
	
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	if(diff <= 0.0) spec = 0.0; 
	vec3 specular = flashlight.specular*spec*vec3(texture(material.specular,TexCoords));


	 
	//这里放光线衰减有关的内容
	float distance = length(flashlight.position - FragPos);
	float attenuation = 1.0/(flashlight.constant +flashlight.linear * distance +flashlight.quadratic*(distance*distance));
	ambient  *= attenuation; 
	diffuse  *= attenuation;
	specular *= attenuation;




	

	float theta = dot(lightDir ,normalize(-flashlight.direction));
	float epsilon = flashlight.cutOff - flashlight.outerCutOff;
	float intensity = clamp((theta - flashlight.outerCutOff) / epsilon, 0.0, 1.0);   


	ambient  *= intensity;
	diffuse  *= intensity;
	specular *= intensity;
	

	vec3 result =ambient + diffuse+specular;
    
    result += CalcDirLight(dirLight,norm,viewDir);
    for(int i = 0 ;i<NR_POINT_LIGHTS;i++){
    result += CalcPointLight(pointLights[i],norm,FragPos,viewDir);

    }


	FragColor = vec4(result,1.0f) ;


} 