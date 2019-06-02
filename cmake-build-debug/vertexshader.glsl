#version 410

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 col;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;


uniform mat4 M;
uniform mat4 MVP;

out vec3 iColor;
out vec3 iNormal;

void main(void){
    iColor = col;
    iNormal = (M * vec4(normal, 1)).rgb;
    gl_Position = MVP * vec4(pos, 1);
}