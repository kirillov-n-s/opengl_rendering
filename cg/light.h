#pragma once
#include <glm/vec3.hpp>

namespace cg
{
    struct light
    {
        glm::vec3 direction;
        float intensity;
    };
}
