#include "../window.h"

namespace cg
{
    void window::resize_callback(GLFWwindow *window, int new_width, int new_height)
    {
        _width = new_width;
        _height = new_height;
        glViewport(0, 0, _width, _height);
    }

    void window::cursor_callback(GLFWwindow *window, double x_pos, double y_pos)
    {
        float x_offset = x_pos - _x_prev;
        float y_offset = _y_prev - y_pos;
        _x_prev = x_pos;
        _y_prev = y_pos;
        _camera.rotate(x_offset * _sensitivity, y_offset * _sensitivity);
    }

    void window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(_window, GLFW_TRUE);

        if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
            glfwMaximizeWindow(_window);

        if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
            _camera = {};

        auto i = key - GLFW_KEY_0;
        if (i >= 0 && i <= 9 && action == GLFW_PRESS && _textures.size() > i)
        {
            _shader->use();
            _shader->set_uniform("uTexture", _textures[_cur_tex_idx = i]->slot());
        }
    }

    void window::prepare()
    {
        _projection = glm::perspective(glm::radians(_fov), _aspect, _near, _far);

        _shader->use();

        _shader->set_uniform("uModel", _model);
        _shader->set_uniform("uNormalModel", _normal_model);
        _shader->set_uniform("uProjection", _projection);

        _shader->set_uniform("uTexture", _textures[_cur_tex_idx]->slot());

        _shader->set_uniform("uAmbient", _material.ambient);
        _shader->set_uniform("uDiffuse", _material.diffuse);
        _shader->set_uniform("uSpecular", _material.specular);
        _shader->set_uniform("uShininess", _material.shininess);

        for (int i = 0; i < _lights.size(); ++i)
        {
            _shader->set_uniform(std::string("uLightDirs[") + std::to_string(i) + "]",
                                 _lights[i].direction);
            _shader->set_uniform(std::string("uLightColors[") + std::to_string(i) + "]",
                                 _lights[i].color * _lights[i].intensity);
        }

        _skybox_shader->use();
        _skybox_shader->set_uniform("uProjection", _projection);
        _skybox_shader->set_uniform("uTexture", _skybox->slot());

        glFrontFace(GL_CCW);
        glEnable(GL_CULL_FACE);
    }

    void window::handle_movement(float frame_time)
    {
        glm::vec3 direction = directions::zero;
        if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
            direction += _camera.front();
        if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
            direction -= _camera.front();
        if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
            direction += _camera.right();
        if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
            direction -= _camera.right();
        if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS)
            direction += directions::up;
        if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS)
            direction -= directions::up;
        _camera.move(direction * frame_time * _speed);
    }

    void window::render()
    {
        auto view = _camera.view();

        _skybox_shader->use();
        _skybox_shader->set_uniform("uView", glm::mat4(glm::mat3(view)));
        _skybox->draw();

        _shader->use();
        _shader->set_uniform("uView", view);
        _shader->set_uniform("uCameraDir", _camera.front());
        _textures[_cur_tex_idx]->use();
        _mesh->draw();
    }

    void window::create(int width, int height)
    {
        _width = width;
        _height = height;
        _aspect = (float)_width / _height;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        _window = glfwCreateWindow(_width, _height, "", nullptr, nullptr);
        if (_window == nullptr)
        {
            glfwTerminate();
            throw std::runtime_error("Cannot open window.");
        }

        glfwMakeContextCurrent(_window);

        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glfwSetFramebufferSizeCallback(_window, resize_callback);
        glfwSetCursorPosCallback(_window, cursor_callback);
        glfwSetKeyCallback(_window, key_callback);

        glViewport(0, 0, _width, _height);

        glewInit();
    }

    void window::load(mesh* mesh, const std::vector<texture*>& textures, shader* shader,
                      skybox* skybox, class shader* skybox_shader,
                      const camera& camera, const material& material, const std::vector<light>& lights)
    {
        _mesh = mesh;
        _textures = textures;
        _shader = shader;
        _skybox = skybox;
        _skybox_shader = skybox_shader;

        _camera = camera;
        _material = material;
        _lights = lights;
    }

    void window::run()
    {
        float current_frame, prev_frame = 0.f, frame_time;

        prepare();

        while(!glfwWindowShouldClose(_window))
        {
            current_frame = glfwGetTime();
            frame_time = current_frame - prev_frame;
            prev_frame = current_frame;

            glfwSetWindowTitle(_window, (std::to_string((int)(1.f / frame_time)) + " fps").c_str());

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            handle_movement(frame_time);
            render();

            glfwSwapBuffers(_window);
            glfwPollEvents();
        }
    }

    void window::destroy()
    {
        glfwTerminate();
    }
}
