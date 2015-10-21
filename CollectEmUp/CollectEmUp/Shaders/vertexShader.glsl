#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 vecTexUV;
layout (location = 2) in vec3 vecNorm;
out vec2 fragTexUV;
out vec3 fragPos;
out vec3 fragNorm;

uniform mat4 viewMatrix;
uniform mat4 worldMatrix;
uniform vec3 scale;

void main()
{
    fragTexUV = vecTexUV;
    fragPos = gl_Position.xyz;
    fragNorm = normalize((worldMatrix * vec4(vecNorm, 0)).xyz);
	gl_Position = viewMatrix *
                  worldMatrix *
                  vec4(position, 1);
}