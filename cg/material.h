#pragma once
#include <glm/vec3.hpp>

namespace cg
{
    struct material
    {
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shininess;

        material() = default;
        material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess);
    };
}
