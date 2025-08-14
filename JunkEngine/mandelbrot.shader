#version 330 core
out vec4 fragColour;
in vec3 vertexColour;
in vec2 pos;
void main()
{
  float x = 0;
  float y = 0;
  float tempX;
  float i = 0;
  float maxIterations = 1000;
  float xOffset = -.75;
  float yOffset = -.3;
  float zoom = 8;
  while (i < maxIterations && x*y+y*y < 4) {
    tempX = x*x-y*y + pos.x/zoom+xOffset;
    y = 2*x*y + pos.y/zoom+yOffset;
    x = tempX;
    ++i;
  }

  fragColour = vec4(0,
                    (maxIterations-i)/maxIterations/2,
                    (maxIterations-i)/maxIterations,
                    1);
  //fragColour = vec4(vertexColour, 1);
}