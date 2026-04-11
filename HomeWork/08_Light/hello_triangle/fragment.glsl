#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
	
	
struct Material{
vec3 ambient;//环境光照  定义了 再环境光照下 表面反射的是什么颜色 通常与表面的颜色相同 
vec3 diffuse;//漫反射光照  这个代表 我们期望物体本身的颜色
vec3 specular;//镜面光照 镜面高光的颜色
float shininess;//反光度  高光的散射（半径）


};
//这里创建的是灯光的结构体
struct Light{
vec3 position;
vec3 ambient;
vec3 diffuse;
vec3 specular;
};


uniform Light light;
uniform Material material;//材质名


uniform vec3 lightPos;
uniform vec3 viewPos;//这个是摄像机的位置  也就是视角位置



void main(){



	vec3 ambient = light.ambient*material.ambient;

	//漫反射光照
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm,lightDir),0.0);

	vec3 diffuse =light.diffuse*(diff*material.diffuse);
	

	//接下来是镜面光照
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	if(diff <= 0.0) spec = 0.0; 
	
	vec3 specular =light.specular*(spec*material.specular);
	vec3 result =ambient + diffuse+specular;

	FragColor = vec4(result,1.0f);



} 