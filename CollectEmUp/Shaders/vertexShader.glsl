#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 vecTexUV;
layout (location = 2) in vec3 vecNorm;
out float fragBrightness;
out vec2 fragTexUV;
out vec3 fragPos;
out vec3 fragNorm;

uniform float brightness;
uniform mat4 viewMatrix;
uniform mat4 worldMatrix;
uniform vec3 scale;

void main()
{
    fragBrightness = brightness;
    fragTexUV = vecTexUV;
    fragPos = gl_Position.xyz;
    fragNorm = normalize((worldMatrix * vec4(vecNorm, 0)).xyz);
	gl_Position = viewMatrix *
                  worldMatrix *
                  vec4(position, 1);
}