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

    void window::prepare()
    {
        _projection = glm::perspective(_fov, _aspect, _near, _far);

        _shader.use();

        _shader.set_uniform("uModel", _model);
        _shader.set_uniform("uNormalModel", _normal_model);
        _shader.set_uniform("uProjection", _projection);

        auto light = _lights[0];
        _shader.set_uniform("uNegLightDir", -light.direction);
        _shader.set_uniform("uAmbient", glm::vec3 { 0.f, 0.1f, 0.2f } * light.intensity);
        _shader.set_uniform("uDiffuse", glm::vec3 { 0.f, 0.25f, 0.5f } * light.intensity);
        _shader.set_uniform("uSpecular", glm::vec3 { 0.5f, 0.5f, 0.5f } * light.intensity);
        _shader.set_uniform("uShininess", 64.f);
    }

    void window::handle_events(float frame_time)
    {
        if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(_window, GLFW_TRUE);

        glm::vec3 direction = directions::zero;
        if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
            direction += _camera.front();
        if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
            direction -= _camera.front();
        if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
            direction += _camera.right();
        if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
            direction -= _camera.right();
        if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS)
            direction += directions::up;
        if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS)
            direction -= directions::up;
        _camera.move(direction * frame_time * _speed);
    }

    void window::render()
    {
        _shader.use();
        _shader.set_uniform("uView", _camera.view());
        _shader.set_uniform("uCameraDir", _camera.front());
        _mesh.draw();
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

        glViewport(0, 0, _width, _height);

        glewInit();
    }

    void window::load(const mesh& mesh, const texture& texture, const shader& shader,
                      const camera& camera, const std::vector<light>& lights)
    {
        _mesh = mesh;
        _texture = texture;
        _shader = shader;
        _camera = camera;
        _lights = lights;
    }

    void window::run()
    {
        float current_frame, prev_frame = 0.f, frame_time;

        prepare();

        glFrontFace(GL_CW);
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);

        while(!glfwWindowShouldClose(_window))
        {
            current_frame = glfwGetTime();
            frame_time = current_frame - prev_frame;
            prev_frame = current_frame;

            glfwSetWindowTitle(_window, (std::to_string((int)(1.f / frame_time)) + " fps").c_str());

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            handle_events(frame_time);
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
