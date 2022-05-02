#include <iostream>
#include <string>
#include "cg/window.h"

const std::string path = R"(C:\Users\user\Desktop\University\Sem2\Graph\laba3\shaders\)";

int main()
{
    cg::window::create(1600, 900);

    auto mesh = cg::make_uv_sphere(1.f, 32, 32);
    cg::shader shader { path + "shader.vert", path + "shader.frag" };
    cg::camera camera { cg::directions::back * 3.f };

    cg::window::load(mesh, {}, shader, camera, { { { 1.f, 1.f, -1.f }, 1.f } });
    cg::window::run();
    cg::window::destroy();
}
