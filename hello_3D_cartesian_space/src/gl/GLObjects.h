#pragma once
#include <glad/gl.h>
#include <iostream>

#ifndef GL_CHECK
#define GL_CHECK(stmt) do { stmt; GLenum err = glGetError(); if (err != GL_NO_ERROR) { \
    std::cerr << "GL error 0x" << std::hex << err << " at " << __FILE__ << ":" << std::dec << __LINE__ \
              << " (" #stmt ")\n"; } } while(0)
#endif

struct VBO {
    GLuint id = 0;
    VBO() { GL_CHECK(glGenBuffers(1, &id)); }
    ~VBO(){ if (id) glDeleteBuffers(1, &id); }
    void bind(GLenum target) const { glBindBuffer(target, id); }
    VBO(const VBO&) = delete; VBO& operator=(const VBO&) = delete;
    VBO(VBO&& o) noexcept { id = o.id; o.id = 0; }
    VBO& operator=(VBO&& o) noexcept { if (this!=&o){ if(id) glDeleteBuffers(1,&id); id=o.id; o.id=0; } return *this; }
};

struct VAO {
    GLuint id = 0;
    VAO() { GL_CHECK(glGenVertexArrays(1, &id)); }
    ~VAO(){ if (id) glDeleteVertexArrays(1, &id); }
    void bind() const { glBindVertexArray(id); }
    VAO(const VAO&) = delete; VAO& operator=(const VAO&) = delete;
    VAO(VAO&& o) noexcept { id = o.id; o.id = 0; }
    VAO& operator=(VAO&& o) noexcept { if (this!=&o){ if(id) glDeleteVertexArrays(1,&id); id=o.id; o.id=0; } return *this; }
};
