#version 330 core

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_diffuse3;

    sampler2D texture_specular1;
    sampler2D texture_specular2;
};

in vec2 texCoords;

uniform vec3 viewPos;
uniform vec3 objectColor;
uniform Material material;

out vec4 fragColor;

void main()
{    
    fragColor = texture(material.texture_diffuse1, texCoords);
}