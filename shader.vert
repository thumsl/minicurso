#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture;

out vec2 fragTexture;

uniform float factor;
uniform mat4 transform;

void main() {
	fragTexture = texture;
	gl_Position = transform * vec4(position, 1.0f);
}