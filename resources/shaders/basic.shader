#shader vertex
#version 330 core

layout(location = 0)  in vec3 position;
layout(location = 1) in vec3 colour;

out vec3 fragColour;

void main()
{
   gl_Position = vec4(position, 1.0);
   fragColour = colour;
};

#shader fragment
#version 330 core
in vec3 fragColour;
out vec4 finalColour;

void main()
{
   finalColour = vec4(fragColour, 1.0);
};