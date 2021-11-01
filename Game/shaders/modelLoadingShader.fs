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

float near = 0.1;
float far  = 100.0;

void main()
{    
    float ndc = gl_FragCoord.z * 2.0 - 1.0;
    float linearDepth = (2.0 * near * far) / (far + near - ndc * (far - near)) / far;
    // fragColor = texture(material.texture_diffuse1, texCoords);
    // fragColor = vec4(objectColor, 1.0);
    fragColor = vec4(vec3(linearDepth), 1.0);
}