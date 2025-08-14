#version 330 core
out vec4 fragColour;
in vec3 vertexColour;
in vec2 pos;
void main()
{

  fragColour = vec4(step(0, pos.x),0,0,1);
  //fragColour = vec4(vertexColour, 1);
}