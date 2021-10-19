#version 330 core

struct Material 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 fragPos;
in vec3 normal;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;  

out vec4 fragColor;

void main()
{
	// Ambient light
	// vec3 ambient = lightColor * material.ambient;
	vec3 ambient  = light.ambient * material.ambient;

	// Diffuse light
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	// vec3 diffuse = lightColor * (diff * material.diffuse);
	vec3 diffuse  = light.diffuse * (diff * material.diffuse);

	// Specular light
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	// vec3 specular = lightColor * (spec * material.specular);
	vec3 specular = light.specular * (spec * material.specular);  

	vec3 result = ambient + diffuse + specular;
	fragColor = vec4(result, 1.0);
}
