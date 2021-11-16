#version 430 core

in vec2 position;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main() {
	gl_Position=projectionMatrix*modelMatrix*vec4(position,0.0,1.0);
}