#version 330

uniform mat4 p_matrix;
uniform mat4 v_matrix;
uniform mat4 m_matrix;

int main() {
    gl_Position = p_matrix*v_matrix*m_matrix;
}