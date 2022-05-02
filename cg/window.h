#pragma once
#include <iostream>
#include <string>
#include "mesh.h"
#include "texture.h"
#include "shader.h"
#include "camera.h"
#include "light.h"
#include <GLFW/glfw3.h>

namespace cg
{
    class window
    {
    private:
        static inline GLFWwindow* _window;
        static inline int _width;
        static inline int _height;
        static inline float _aspect;

        static inline mesh _mesh;
        static inline texture _texture;
        static inline shader _shader;
        static inline camera _camera;
        static inline std::vector<light> _lights;

        static inline float _x_prev;
        static inline float _y_prev;

        static inline float _sensitivity = 0.1f;
        static inline float _speed = 2.5f;

        static inline float _fov = 45.f;
        static inline float _near = 0.1f;
        static inline float _far = 100.f;

        static inline glm::mat4 _projection;
        static inline glm::mat4 _model = glm::mat4 { 1.f };
        static inline glm::mat4 _normal_model = glm::transpose(glm::inverse(_model));

        static void resize_callback(GLFWwindow* window, int new_width, int new_height);
        static void cursor_callback(GLFWwindow* window, double x_pos, double y_pos);

        static void prepare();
        static void handle_events(float frame_time);
        static void render();

    public:
        static void create(int width, int height);
        static void load(const mesh& mesh, const texture& texture, const shader& shader,
                         const camera& camera, const std::vector<light>& lights);
        static void run();
        static void destroy();
    };
}
