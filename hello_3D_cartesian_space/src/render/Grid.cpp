#include "Grid.h"

Grid::Grid(int halfExtent, float step) {
    build(halfExtent, step);

    vao_ = VAO{};
    vbo_ = VBO{};

    vao_.bind();
    vbo_.bind(GL_ARRAY_BUFFER);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size()*sizeof(float), vertices_.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    glBindVertexArray(0);
}

void Grid::line(float x1,float y1,float z1, float x2,float y2,float z2) {
    vertices_.push_back(x1); vertices_.push_back(y1); vertices_.push_back(z1);
    vertices_.push_back(x2); vertices_.push_back(y2); vertices_.push_back(z2);
}

void Grid::build(int halfExtent, float step) {
    float min = -halfExtent * step;
    float max =  halfExtent * step;

    for (int i = -halfExtent; i <= halfExtent; ++i) {
        float v = i * step;
        // Lines parallel to X at z = v
        line(min, 0.0f, v,  max, 0.0f, v);
        // Lines parallel to Z at x = v
        line(v, 0.0f, min,  v,   0.0f, max);
    }

    gridVertexCount_ = vertices_.size() / 3; // vertices (not floats)

    // Axes: X, Z, Y
    line(min, 0.0f, 0.0f, max, 0.0f, 0.0f); // X
    line(0.0f, 0.0f, min, 0.0f, 0.0f, max); // Z
    line(0.0f, min, 0.0f, 0.0f, max, 0.0f); // Y

    axesVertexCount_ = vertices_.size()/3 - gridVertexCount_;
}

void Grid::drawGrid() const {
    vao_.bind();
    glDrawArrays(GL_LINES, 0, (GLsizei)gridVertexCount_);
    glBindVertexArray(0);
}

void Grid::drawAxes() const {
    vao_.bind();
    glDrawArrays(GL_LINES, (GLint)gridVertexCount_, (GLsizei)axesVertexCount_);
    glBindVertexArray(0);
}
