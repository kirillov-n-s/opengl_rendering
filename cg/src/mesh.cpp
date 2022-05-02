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

    mesh* make_uv_sphere(float radius, int row_count, int col_count)
    {
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        float row_step = pi / row_count;
        float col_step = 2 * pi / col_count;
        float inv_radius = 1.0f / radius;

        float row_angle, col_angle, x, y, z, xy;
        for (int i = 0; i <= row_count; ++i)
        {
            row_angle = pi / 2 - i * row_step;
            xy = radius * cosf(row_angle);
            z = radius * sinf(row_angle);

            for (int j = 0; j <= col_count; ++j)
            {
                col_angle = j * col_step;
                x = xy * cosf(col_angle);
                y = xy * sinf(col_angle);

                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);

                vertices.push_back(x * inv_radius);
                vertices.push_back(y * inv_radius);
                vertices.push_back(z * inv_radius);

                vertices.push_back((float)j / col_count);
                vertices.push_back((float)i / row_count);
            }
        }

        /*
         *  t--t+1
         *  |  / |
         *  | /  |
         *  b--b+1
         */
        unsigned int top, bottom;
        for(int i = 0; i < row_count; ++i)
        {
            top = i * (col_count + 1);
            bottom = top + col_count + 1;

            for(int j = 0; j < col_count; ++j, ++top, ++bottom)
            {
                if (i != 0)
                {
                    indices.push_back(top);
                    indices.push_back(bottom);
                    indices.push_back(top + 1);
                }

                if (i != (row_count - 1))
                {
                    indices.push_back(top + 1);
                    indices.push_back(bottom);
                    indices.push_back(bottom + 1);
                }
            }
        }

        return new mesh { vertices, indices };
    }
}