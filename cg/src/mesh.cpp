#include "../mesh.h"

namespace cg
{
    mesh::mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
        : _vertices(vertices), _indices(indices)
    {
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
        glEnableVertexAttribArray(2);

        glGenBuffers(1, &_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    mesh::~mesh()
    {
        glDeleteVertexArrays(1, &_vao);
        glDeleteBuffers(1, &_vbo);
        glDeleteBuffers(1, &_ebo);
    }

    void mesh::draw() const
    {
        glBindVertexArray(_vao);
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

    mesh make_uv_sphere(float radius, int rows, int cols)
    {
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        float row_delta = pi / rows;
        float col_delta = 2.f * pi / cols;
        float inv_length = 1.f / radius;

        float row_angle, col_angle, x, y, z, xy;

        for (int i = 0; i <= rows; ++i)
        {
            row_angle = pi * 0.5f - i * row_delta;
            xy = radius * cosf(row_angle);
            z = radius * sinf(row_angle);

            for (int j = 0; j <= cols; ++j)
            {
                col_angle = j * col_delta;

                x = xy * cosf(col_angle);
                y = xy * sinf(col_angle);

                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);

                vertices.push_back(x * inv_length);
                vertices.push_back(y * inv_length);
                vertices.push_back(z * inv_length);

                vertices.push_back((float)j / cols);
                vertices.push_back((float)i / rows);
            }
        }

        unsigned int top, bottom;

        top = 0;
        bottom = cols + 1;
        for (int j = 0; j < cols; ++j, ++top, ++bottom)
        {
            indices.push_back(top + 1);
            indices.push_back(bottom);
            indices.push_back(bottom + 1);
        }

        for (int i = 1; i < rows - 1; ++i)
        {
            top = i * (cols + 1);
            bottom = top + cols + 1;
            for (int j = 0; j < cols; ++j, ++top, ++bottom)
            {
                indices.push_back(top);
                indices.push_back(bottom);
                indices.push_back(top + 1);
                indices.push_back(top + 1);
                indices.push_back(bottom);
                indices.push_back(bottom + 1);
            }
        }

        top = (rows - 1) * (cols + 1);
        bottom = top + cols + 1;
        for (int j = 0; j < cols; ++j, ++top, ++bottom)
        {
            indices.push_back(top);
            indices.push_back(bottom);
            indices.push_back(top + 1);
        }

        return { vertices, indices };
    }
}