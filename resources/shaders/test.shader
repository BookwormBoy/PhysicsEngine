#shader vertex
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;

out vec2 texCoord;

void main()
{
   gl_Position = vec4(aPosition, 1.0);
   texCoord = aTexCoord;
};

#shader fragment
#version 330 core

in vec2 texCoord;

out vec4 fragColour;

void main()
{
   fragColour = vec4(1.0f, 0.0f, 0.0f, 1.0f);
};