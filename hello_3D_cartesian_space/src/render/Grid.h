#pragma once
#include <vector>
#include <glad/gl.h>
#include "../gl/GLObjects.h"

// Grid geometry on XZ plane plus XYZ axes, with separate draw ranges for coloring.
class Grid {
public:
    Grid(int halfExtent = 10, float step = 1.0f);

    void drawGrid() const; // draw only grid lines
    void drawAxes() const; // draw only axes

private:
    void line(float x1,float y1,float z1, float x2,float y2,float z2);
    void build(int halfExtent, float step);

    std::vector<float> vertices_;
    size_t gridVertexCount_ = 0;  // number of vertices in grid (not floats)
    size_t axesVertexCount_ = 0;  // number of vertices in axes

    VAO vao_{};
    VBO vbo_{};
};
