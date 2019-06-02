#version 410

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 col;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;

layout(location = 4) in vec3 pos2;
layout(location = 5) in vec3 norm2;

uniform float interpolationFactor;
uniform mat4 M;
uniform mat4 MVP;

out vec3 iColor;
out vec3 iNormal;

void main(void){
    vec3 Pos  = mix(pos, pos2,interpolationFactor);
    vec3 Norm = normalize( mix(normal, norm2, interpolationFactor) );

//    vec3 Pos = pos2;
//    vec3 Norm = norm2;

    iColor = col;
    iNormal = (M * vec4(Norm, 1)).rgb;
    gl_Position = MVP * vec4(Pos, 1);
}