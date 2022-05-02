#pragma once
#include <glm/vec3.hpp>

namespace cg::directions
{
    const glm::vec3 zero = { 0.f, 0.f, 0.f };
    const glm::vec3 right = { 1.f, 0.f, 0.f };
    const glm::vec3 left = { -1.f, 0.f, 0.f };
    const glm::vec3 up = { 0.f, 1.f, 0.f };
    const glm::vec3 down = { 0.f, -1.f, 0.f };
    const glm::vec3 back = { 0.f, 0.f, 1.f };
    const glm::vec3 front = { 0.f, 0.f, -1.f };
}
