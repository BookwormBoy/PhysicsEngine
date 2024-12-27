#shader vertex
#version 330 core

layout(location = 0)  in vec4 position;
out vec4 fragPosition;

void main()
{
   gl_Position = position;
   fragPosition=position;
};

#shader fragment
#version 330 core
in vec4 fragPosition;
layout(location = 0)  out vec4 colour;

uniform vec4 u_Colour;

void main()
{
   colour = u_Colour;
};