#shader vertex
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;

// uniform float offset;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection*view*model*vec4(aPosition, 1.0);
   texCoord = aTexCoord;
};

#shader fragment
#version 330 core

in vec2 texCoord;

out vec4 fragColour;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
   fragColour = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);
};