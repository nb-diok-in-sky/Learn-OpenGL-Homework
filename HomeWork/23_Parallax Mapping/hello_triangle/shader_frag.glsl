#version 330 core
out vec4 FragColor;

in VS_OUT{
vec3 FragPos;
vec2 TexCoords;
vec3 TangentLightPos;
vec3 TangentViewPos;
vec3 TangentFragPos;


}fs_in;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D depthMap;
uniform bool parallax;
uniform float height_scale;



vec2 ParallaxMapping(vec2 texCoords,vec3 viewDir){

const float minLayers  = 8;
const float maxLayers = 32;
float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));


float layerDepth = 1.0/numLayers;
float currentLayerDepth = 0.0;

vec2 P = viewDir.xy * height_scale;
vec2 deltaTexCoords = P/numLayers;

vec2 currentTexCoords = texCoords;
float currentDepthMapValue = texture(depthMap,currentTexCoords).r;
while(currentLayerDepth < currentDepthMapValue)
{
    // shift texture coordinates along direction of P
    currentTexCoords -= deltaTexCoords;
    // get depthmap value at current texture coordinates
    currentDepthMapValue = texture(depthMap, currentTexCoords).r;  
    // get depth of next layer
    currentLayerDepth += layerDepth;  
}


vec2 preTexCoords = currentTexCoords +deltaTexCoords ;

float afterDepth = currentDepthMapValue - currentLayerDepth;
float beforeDepth =texture(depthMap,preTexCoords).r - currentLayerDepth +layerDepth;

float weight = afterDepth /(afterDepth - beforeDepth);
vec2 finalTexCoords = preTexCoords * weight +currentTexCoords * (1.0- weight);





return finalTexCoords;
}



void main(){
 
 vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
 vec2 texCoords = fs_in.TexCoords;
 if(parallax){
 texCoords = ParallaxMapping(fs_in.TexCoords,viewDir);

 vec3 normal = texture(normalMap , texCoords).rgb;

 vec3 color = texture(diffuseMap,texCoords).rgb;
 vec3 ambient = 0.1*color;
 vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
 float diff = max(dot(lightDir,normal),0.0);
 vec3 diffuse = diff*color;
     vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 specular = vec3(0.2) * spec;
    FragColor = vec4(ambient + diffuse + specular, 1.0f);


 }

}




