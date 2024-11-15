#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aCol;

uniform vec3 offset = vec3(0.,0.,0.);

out vec4 planeColor;

void main()
{
    vec3 pos = aPos + offset;
    gl_Position = vec4(pos, 1.0);
    planeColor = aCol;
}