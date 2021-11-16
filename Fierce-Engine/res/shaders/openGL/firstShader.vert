#version 430 core

in vec2 inPosition;
in vec3 inColor;

out vec3 fragColor;

void main() {
	gl_Position = vec4(inPosition, 0.0, 1.0);
    fragColor = inColor;
}