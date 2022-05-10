#include "cg/window.h"

const std::string path = R"(C:\Users\user\Desktop\University\Sem2\Graph\laba3\)";
const std::string shader_path = path + R"(shaders\)";
const std::string texture_path = path + R"(textures\)";
const std::string skybox_path = path + R"(skyboxes\)";

int main()
{
    cg::window::create(1600, 900);

    auto mesh = cg::make_uv_sphere(1.f, 32, 32);
    std::vector<cg::texture*> textures
    {
        new cg::texture { texture_path + "earth.jpg" },
        new cg::texture { texture_path + "moon.jpg" },
        new cg::texture { texture_path + "mars.jpg" },
        new cg::texture { texture_path + "jupiter.jpg" },
        new cg::texture { texture_path + "saturn.jpg" },
        new cg::texture { texture_path + "uranus.jpg" },
        new cg::texture { texture_path + "neptune.jpg" },
        new cg::texture { texture_path + "roflan.png" },
        new cg::texture { texture_path + "amogus.png" },
        new cg::texture { texture_path + "orehus.png" },
    };
    auto shader = new cg::shader {shader_path + "main.vert", shader_path + "main.frag" };

    std::string face_paths[] = {
        skybox_path + "right.png",
        skybox_path + "left.png",
        skybox_path + "top.png",
        skybox_path + "bottom.png",
        skybox_path + "back.png",
        skybox_path + "front.png"
    };
    auto skybox = new cg::skybox { face_paths };
    auto skybox_shader = new cg::shader { shader_path + "skybox.vert", shader_path + "skybox.frag" };

    cg::window::load(mesh, textures, shader, skybox, skybox_shader,
                     cg::camera {},
                     cg::material
                     {
                         glm::vec3 { 0.1f },
                         glm::vec3 { 0.5f },
                         glm::vec3 { 1.f },
                         32.f
                     },
                     { {
                         cg::light
                         {
                             { -1.f, 0.f, 0.f },
                             { 1.f, 1.f, 0.25f },
                             1.f
                         },
                         cg::light
                         {
                             { 0.f, 0.f, -1.f },
                             { 0.25f, 1.f, 1.f },
                             0.5f
                         },
                         cg::light
                         {
                             { 0.f, 1.f, 0.f },
                             { 1.f, 0.25f, 1.f },
                             1.5f
                         }
                     } });
    cg::window::run();
    cg::window::destroy();

    delete mesh;
    for (auto& texture : textures)
        delete texture;
    delete shader;
    delete skybox;
    delete skybox_shader;
}
