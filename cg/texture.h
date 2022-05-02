#pragma once
#include <stdexcept>
#include <string>
#include "../stb_image/stb_image.h"
#include <GL/glew.h>

namespace cg
{
    int texture_slots_used();

    class texture
    {
    private:
        unsigned int _id;
        int _slot;

    public:
        texture(const std::string& path);

        void use() const;

        int slot() const;
    };
}
