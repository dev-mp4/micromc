#version 330 core

in vec2 f_uv;

out vec4 color;

uniform sampler2D u_texture0;

void main() {
    color = texture(u_texture0, f_uv);
}