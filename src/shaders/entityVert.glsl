#version 330 core

// input variables
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

// output variables
out vec4 ourColor;

// uniform variables
uniform mat4 Projection;
uniform mat4 Model;

void main()
{
    gl_Position = Projection * Model * vec4(aPos, 1.0);
    ourColor = aColor;
}  

