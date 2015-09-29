#version 330

layout (location = 0) in vec3 position;

uniform mat4 worldMatrix;
uniform mat4 objMatrix;
uniform vec3 scale;

void main()
{
	gl_Position = worldMatrix * objMatrix * vec4(position * scale, 1);
}