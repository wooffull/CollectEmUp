#version 330

layout (location = 0) in vec2 position;

uniform mat4 worldMatrix;
uniform mat4 objMatrix;
uniform vec2 offset;
uniform vec2 scale;

void main()
{
	gl_Position = worldMatrix * objMatrix * vec4(position * scale + offset, 0, 1);
}