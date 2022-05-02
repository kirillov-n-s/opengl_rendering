#pragma once
#include <vector>
#include <GL/glew.h>

namespace cg
{
    constexpr float pi = 3.14159265f;

    class mesh
    {
    private:
        std::vector<float> _vertices;
        std::vector<unsigned int> _indices;

        unsigned int _vbo, _vao, _ebo;

    public:
        mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
        ~mesh();

        void draw() const;
    };

    mesh* make_uv_sphere(float radius, int row_count, int col_count);
}
