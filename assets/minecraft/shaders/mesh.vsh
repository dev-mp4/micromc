#version 330 core

layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec2 v_uv;

out vec2 f_uv;

uniform mat4 model;
uniform mat4 projview;

void main() {
    f_uv = v_uv;
    gl_Position = projview * model * vec4(v_pos, 1.0);
}