#include "../camera.h"

namespace cg
{
    void camera::update_derived_vectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        front.y = sin(glm::radians(_pitch));
        front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

        _front = glm::normalize(front);
        _right = glm::normalize(glm::cross(_front, directions::up));
        _up = glm::cross(_right, _front);
    }

    camera::camera(const glm::vec3 &position, float yaw, float pitch)
        : _position(position), _yaw(yaw), _pitch(pitch)
    {
        update_derived_vectors();
    }

    glm::vec3 camera::front() const
    {
        return _front;
    }

    glm::vec3 camera::right() const
    {
        return _right;
    }

    glm::vec3 camera::up() const
    {
        return _up;
    }

    glm::mat4 camera::view() const
    {
        return glm::lookAt(_position, _position + _front, _up);
    }

    void camera::move(const glm::vec3 &offset)
    {
        _position += offset;
    }

    void camera::rotate(float yaw_offset, float pitch_offset)
    {
        _yaw += yaw_offset;
        _pitch += pitch_offset;
        if (_pitch > 89.0f)
            _pitch = 89.0f;
        if (_pitch < -89.0f)
            _pitch = -89.0f;
        update_derived_vectors();
    }
}
