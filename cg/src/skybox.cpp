#include "../skybox.h"

namespace cg
{
    skybox::skybox(const std::string face_paths[6])
        : _slot(texture_slots_used())
    {
        glGenTextures(1, &_id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _id);

        int width, height, channels;
        for (int i = 0; i < 6; i++)
        {
            auto* data = stbi_load(face_paths[i].c_str(),
                                           &width, &height, &channels, 0);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
                         width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
    }

    skybox::~skybox()
    {
        glDeleteTextures(1, &_id);
        glDeleteBuffers(1, &_vbo);
        glDeleteVertexArrays(1, &_vao);
    }

    void skybox::draw() const
    {
        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        glDisable(GL_CULL_FACE);
        glDepthMask(GL_FALSE);

        glActiveTexture(GL_TEXTURE0 + _slot);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _id);

        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glDepthMask(GL_TRUE);
        glEnable(GL_CULL_FACE);
        glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    }

    int skybox::slot() const
    {
        return _slot;
    }
}
