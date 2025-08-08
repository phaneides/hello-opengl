#pragma once
#include <glad/gl.h>
#include <iostream>
#include "../math/Math.h"

inline GLuint compileShader(GLenum type, const char* src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    GLint ok = 0; glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetShaderInfoLog(s, sizeof(log), nullptr, log);
        std::cerr << "Shader compile error: " << log << "\n";
    }
    return s;
}

inline GLuint makeProgram(const char* vs, const char* fs) {
    GLuint v = compileShader(GL_VERTEX_SHADER, vs);
    GLuint f = compileShader(GL_FRAGMENT_SHADER, fs);
    GLuint p = glCreateProgram();
    glAttachShader(p, v);
    glAttachShader(p, f);
    glLinkProgram(p);
    GLint ok = 0; glGetProgramiv(p, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetProgramInfoLog(p, sizeof(log), nullptr, log);
        std::cerr << "Program link error: " << log << "\n";
    }
    glDeleteShader(v);
    glDeleteShader(f);
    return p;
}

class Shader {
public:
    GLuint prog = 0;
    Shader(const char* vs, const char* fs) { prog = makeProgram(vs, fs); }
    ~Shader() { if (prog) glDeleteProgram(prog); }
    void use() const { glUseProgram(prog); }
    GLint loc(const char* name) const { return glGetUniformLocation(prog, name); }
    void setMat4(const char* name, const Mat4& M) const {
        glUniformMatrix4fv(loc(name), 1, GL_FALSE, M.m);
    }
    void setVec3(const char* name, float x, float y, float z) const {
        glUniform3f(loc(name), x, y, z);
    }
    Shader(const Shader&) = delete; Shader& operator=(const Shader&) = delete;
    Shader(Shader&& o) noexcept { prog = o.prog; o.prog = 0; }
    Shader& operator=(Shader&& o) noexcept { if (this!=&o){ if(prog) glDeleteProgram(prog); prog=o.prog; o.prog=0; } return *this; }
};
