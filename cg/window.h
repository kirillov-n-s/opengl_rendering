#pragma once
#include <iostream>
#include <string>
#include "mesh.h"
#include "texture.h"
#include "shader.h"
#include "camera.h"
#include "light.h"
#include "material.h"
#include "skybox.h"
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

        static inline mesh* _mesh;
        static inline shader* _shader;
        static inline skybox* _skybox;
        static inline shader* _skybox_shader;
        static inline std::vector<texture*> _textures;
        static inline int _cur_tex_idx = 0;

        static inline camera _camera;
        static inline material _material;
        static inline std::vector<light> _lights;

        static inline float _x_prev;
        static inline float _y_prev;

        static inline float _sensitivity = 0.1f;
        static inline float _speed = 2.5f;

        static inline float _fov = 45.f;
        static inline float _near = 0.1f;
        static inline float _far = 100.f;

        static inline glm::mat4 _projection;
        static inline glm::mat4 _model = glm::rotate(glm::mat4 { 1.f }, -pi * 0.5f, { 1.f, 0.f, 0.f });
        static inline glm::mat4 _normal_model = glm::transpose(glm::inverse(_model));

        static void resize_callback(GLFWwindow* window, int new_width, int new_height);
        static void cursor_callback(GLFWwindow* window, double x_pos, double y_pos);
        static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

        static void prepare();
        static void handle_movement(float frame_time);
        static void render();

    public:
        static void create(int width, int height);
        static void load(mesh* mesh, const std::vector<texture*>& textures, shader* shader,
                         skybox* skybox, class shader* skybox_shader,
                         const camera& camera, const material& material, const std::vector<light>& lights);
        static void run();
        static void destroy();
    };
}
