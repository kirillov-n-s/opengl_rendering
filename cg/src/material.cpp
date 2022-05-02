#include "../material.h"

namespace cg
{
    material::material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess)
        : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess)
    {}
}
