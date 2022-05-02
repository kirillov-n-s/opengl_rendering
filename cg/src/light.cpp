#include "../light.h"

namespace cg
{
    light::light(const glm::vec3 &direction, const glm::vec3 &color, float intensity)
        : direction(direction), color(color), intensity(intensity)
    {}
}
