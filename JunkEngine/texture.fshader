#version 330 core
out vec4 fragColour;
in vec3 vertexColour;
in vec2 pos;
in vec2 texCoord;

uniform sampler2D currentTexture;

void main()
{

  //fragColour = vec4(step(0, pos.x),0,0,1);
  fragColour = texture(currentTexture, texCoord)+vec4(vertexColour, 1);
}