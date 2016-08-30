#version 330

out vec4 outColor;

in vec2 fragTexture;

uniform sampler2D sampler;

void main() {
	outColor = texture2D(sampler, fragTexture);
}