#version 330 core
out vec4 fragColour;
in vec3 vertexColour;
in vec2 pos;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixAmount;

void main()
{

  fragColour = mix(texture(texture1, texCoord), texture(texture2, texCoord), mixAmount);
}