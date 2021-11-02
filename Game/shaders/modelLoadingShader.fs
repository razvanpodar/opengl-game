#version 330 core

in vec2 texCoords;

uniform vec3 viewPos;
uniform vec3 objectColor;

uniform sampler2D texture1;

out vec4 fragColor;

void main()
{    
   vec4 texColor = texture(texture1, texCoords);
   if(texColor.a < 0.1)
		discard;
   fragColor = texColor;
}