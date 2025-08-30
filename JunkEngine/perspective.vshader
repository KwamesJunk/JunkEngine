#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 inColour;
layout (location = 2) in vec2 inTexCoord;
out vec3 vertexColour;
out vec2 pos;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
 // note that we read the multiplication from right to left
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    
   //gl_Position = transform * vec4(aPos, 1.0);
   vertexColour = inColour;
   pos = aPos.xy;
   texCoord = inTexCoord;
}