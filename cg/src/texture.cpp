#include "../texture.h"

namespace cg
{
    int texture_slots_used()
    {
        static int count = 0;
        return count++;
    }

    texture::texture(const std::string &path)
        : _slot(texture_slots_used())
    {
        int width, height, channels;
        auto* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        auto format = channels == 3 ? GL_RGB : GL_RGBA;

        glGenTextures(1, &_id);
        glBindTexture(GL_TEXTURE_2D, _id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height,
                     0, format, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    void texture::use() const
    {
        glActiveTexture(GL_TEXTURE0 + _slot);
        glBindTexture(GL_TEXTURE_2D, _id);
    }

    int texture::slot() const
    {
        return _slot;
    }
}