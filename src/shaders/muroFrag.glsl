// base di riferimento presa da: https://www.shadertoy.com/view/flSBDK

#version 330 core

in vec4 planeColor;

out vec4 FragColor;

uniform vec2 resolution;
uniform float currentTime;

void main()
{
    vec2 uv = gl_FragCoord.xy / resolution.xy;

    float scale = 70.;
    float width = 3.;
    float height = 2.;

    vec2 localUV = uv * scale;
    localUV.y += currentTime*30;
    
    float xOffset = mod(localUV.y, height * 2.);
    xOffset = step(height, xOffset);
    
    localUV.x += xOffset;
    localUV.x = mod(localUV.x, height);
    localUV.y = mod(localUV.y, 2.);
    localUV -= vec2(1, 1);
   
    float mask = 1. - step(.8, localUV.y) * step(-.8, localUV.y);
    mask *= 1. - (step(0.9, localUV.x) * step(-.9, localUV.x));
    
    vec3 brickColor = mask * vec3(1., .3, 0);
    vec3 mortarColor = (1. - mask) * vec3(1., .85, .7);
    
    FragColor = vec4(brickColor + mortarColor, 1.0);
}