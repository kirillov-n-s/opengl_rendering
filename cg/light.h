#pragma once
#include <glm/vec3.hpp>

namespace cg
{
    struct light
    {
        glm::vec3 direction;
        glm::vec3 color;
        float intensity;

        light(const glm::vec3& direction, const glm::vec3& color, float intensity);
    };
}
