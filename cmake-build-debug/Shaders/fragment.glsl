#version 410

in vec3 iColor;
in vec2 iTexCoord;
in vec3 iNormal;

layout(location = 0) out vec4 out_Color;

void main() {
    vec3 lightDir = normalize(vec3(1, -1, 0));
    vec3 Normal = normalize(iNormal);
    float attenuation = max(dot(Normal, lightDir), 0.0);
    out_Color = vec4( attenuation * iColor, 1);
}