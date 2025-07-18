#shader vertex
#version 330 core

layout(location = 0) in vec3 aPosition;

// uniform float offset;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection*view*model*vec4(aPosition, 1.0);
};

#shader fragment
#version 330 core

out vec4 FragColor;

uniform vec4 colour;  // Line color

void main() {
    FragColor = colour;
};
