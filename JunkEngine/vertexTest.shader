#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 inColour;
layout (location = 2) in vec2 inTexCoord;
out vec3 vertexColour;
out vec2 pos;
out vec2 texCoord;

void main()
{
   gl_Position = vec4(aPos, 1.0);
   vertexColour = inColour;
   pos = aPos.xy;
   texCoord = inTexCoord;
}