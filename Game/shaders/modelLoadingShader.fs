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
uniform Material material;
uniform sampler2D texture_diffuse1;

out vec4 fragColor;

void main()
{    
    fragColor = texture(material.texture_diffuse1, texCoords);
    // fragColor = vec4(vec3(0.4f, 0.3f, 0.1f), 1.0);
}