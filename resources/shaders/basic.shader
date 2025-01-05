#shader vertex
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColour;
layout(location = 2) in vec2 aTexCoord;

// uniform float offset;

out vec3 colour;
out vec2 texCoord;

void main()
{
   gl_Position = vec4(aPosition, 1.0);
   colour = aColour;
   texCoord = aTexCoord;
};

#shader fragment
#version 330 core

in vec3 colour;
in vec2 texCoord;

out vec4 fragColour;

uniform sampler2D woodTexture;
uniform sampler2D awesomeFace;

void main()
{
   fragColour = mix(texture(woodTexture, texCoord), texture(awesomeFace, texCoord), 0.2);
};