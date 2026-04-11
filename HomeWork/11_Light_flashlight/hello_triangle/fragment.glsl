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
struct Light{
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


uniform sampler2D texture1;
 
uniform Light light;
uniform Material material;//材质名
uniform vec3 viewPos;//这个是摄像机的位置  也就是视角位置



void main(){


	//漫反射光照
	vec3 norm = normalize(Normal);
	

	vec3 lightDir = normalize(light.position - FragPos );

	float diff = max(dot(norm,lightDir),0.0);


	vec3 diffuse =diff * light.diffuse*vec3(texture(material.diffuse,TexCoords));
	vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords));

	//接下来是镜面光照
	vec3 viewDir = normalize(viewPos - FragPos);	
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	if(diff <= 0.0) spec = 0.0; 
	
	vec3 specular = light.specular*spec*vec3(texture(material.specular,TexCoords));


	//这里放光线衰减有关的内容
	float distance = length(light.position - FragPos);
	float attenuation = 1.0/(light.constant +light.linear * distance +light.quadratic*(distance*distance));
	ambient  *= attenuation; 
	diffuse  *= attenuation;
	specular *= attenuation;




	

	float theta = dot(lightDir ,normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);   


	ambient  *= intensity;
	diffuse  *= intensity;
	specular *= intensity;
	

	vec3 result =ambient + diffuse+specular;

	
	FragColor = vec4(result,1.0f) ;


} 