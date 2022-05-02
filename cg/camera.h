#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "directions.h"

namespace cg
{
    class camera
    {
    private:
        glm::vec3 _position;
        float _yaw;
        float _pitch;

        glm::vec3 _front;
        glm::vec3 _right;
        glm::vec3 _up;

        void update_derived_vectors();

    public:
        camera(const glm::vec3& position = cg::directions::back * 3.f, float yaw = -90.f, float pitch = 0.f);

        glm::vec3 front() const;
        glm::vec3 right() const;
        glm::vec3 up() const;

        glm::mat4 view() const;

        void move(const glm::vec3& offset);
        void rotate(float yaw_offset, float pitch_offset);
    };
}
