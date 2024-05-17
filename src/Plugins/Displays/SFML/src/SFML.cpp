/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SFML
*/

#include "SFML.hpp"

#include "imgui-SFML.h"
#include "imgui.h"

namespace rt
{
    SFML::SFML(const uint32_t width, const uint32_t height, const std::string &title)
    {
        _window.create(sf::VideoMode(width, height), title);
        _window.setFramerateLimit(60);

        if (!ImGui::SFML::Init(_window))
            throw std::runtime_error("Failed to initialize ImGui-SFML");
    }

    SFML::~SFML()
    {
        _window.close();
        ImGui::SFML::Shutdown();
    }

    void SFML::run(std::shared_ptr<Scene> parser)
    {
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        auto camera = parser->getCamera();

        ImageTexture image{camera->getResolution()};
        sf::Sprite sprite(image.getTexture());
        camera->asyncDrawImage(parser->getPrimitives(), parser->getLights(), image);

        bool isSaving = false;
        bool isOpeningCfgFile = false;
        bool isPreviewing = false;
        static char filename[256] = {};
        float zoomInImage = 0.5f;

        sf::Clock deltaClock;
        while (_window.isOpen()) {
            sf::Event event{};
            while (_window.pollEvent(event)) {
                ImGui::SFML::ProcessEvent(_window, event);
                if (event.type == sf::Event::Closed)
                    _window.close();
            }

            ImGui::SFML::Update(_window, deltaClock.restart());

            ImGui::BeginMainMenuBar();
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Save image as"))
                    isSaving = true;
                if (ImGui::MenuItem("Open cfg file"))
                    isOpeningCfgFile = true;
                ImGui::Separator();
                if (ImGui::MenuItem("Quit"))
                    _window.close();
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("View")) {
                if (ImGui::MenuItem("Reset layout")) {
                }
                if (ImGui::MenuItem("Camera", nullptr, false, false)) {
                }
                if (ImGui::MenuItem("Lights", nullptr, false, false)) {
                }
                if (ImGui::MenuItem("Primitives", nullptr, false, false)) {
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();

            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

            if (isSaving) {
                ImGui::Begin("Save image as", &isSaving, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
                ImGui::InputText("Filename", filename, IM_ARRAYSIZE(filename));
                ImGui::Text("You must provide a file extension in the filename");
                if (ImGui::Button("Save"))
                    isSaving = !image.getTexture().copyToImage().saveToFile(filename);
                ImGui::SameLine();
                if (ImGui::Button("Close"))
                    isSaving = false;
                ImGui::End();
            }

            if (isOpeningCfgFile) {
                ImGui::Begin("Open cfg file", &isOpeningCfgFile, ImGuiWindowFlags_NoCollapse);
                ImGui::InputText("Filename", filename, IM_ARRAYSIZE(filename));
                ImGui::Checkbox("Preview", &isPreviewing);
                ImGui::Text("Warning: This will close the current scene");
                if (ImGui::Button("Open")) {
                    try {
                        parser = std::make_shared<Scene>(std::filesystem::absolute(filename).string());
                        camera = parser->getCamera();
                        if (isPreviewing) {
                            if (const auto [width, height] = camera->getResolution(); width < 400)
                                camera->setResolution(width, height);
                            else
                                camera->setResolution(400, 400 * height / width);
                            zoomInImage = 1.0f;
                        }
                        image.setSize(camera->getResolution());
                        camera->asyncDrawImage(parser->getPrimitives(), parser->getLights(), image);
                    } catch (const std::exception &e) {
                        std::cerr << e.what() << std::endl;
                    }
                    isOpeningCfgFile = false;
                }
                ImGui::SameLine();
                if (ImGui::Button("Close")) {
                    isOpeningCfgFile = false;
                }
                ImGui::End();
            }

            ImGui::Begin("Image", nullptr, ImGuiWindowFlags_NoResize);
            image.updateTexture();
            ImGui::SliderFloat("Zoom", &zoomInImage, 0.1f, 2.0f);
            sprite.setScale(zoomInImage, zoomInImage);
            ImGui::Image(sprite);
            ImGui::End();

            ImGui::Begin("Camera");
            ImGui::Text("Origin: %.2f %.2f %.2f", camera->getOrigin().x, camera->getOrigin().y, camera->getOrigin().z);
            ImGui::Text("Direction: %.2f %.2f %.2f", camera->getDirection().x, camera->getDirection().y,
                        camera->getDirection().z);
            ImGui::Text("Resolution: %dx%d", camera->getResolution().first, camera->getResolution().second);
            ImGui::Text("Fov: %d", camera->getFieldOfView());
            ImGui::End();

            {
                ImGui::Begin("Lights");
                uint16_t lightCounter = 1;
                for (auto &light : parser->getLights()) {
                    ImGui::Text("Light %u", lightCounter);
                    ImGui::Text("Origin: %.2f %.2f %.2f", light->getOrigin().x, light->getOrigin().y,
                                light->getOrigin().z);
                    ImGui::Text("Color: %.2f %.2f %.2f", light->getColor().r, light->getColor().g, light->getColor().b);
                    ImGui::Text("Intensity: %.2f", light->getIntensity());
                    ImGui::Separator();
                    lightCounter++;
                }
                ImGui::End();
            }

            {
                ImGui::Begin("Primitives");
                uint16_t primitiveCounter = 1;
                for (auto &primitive : parser->getPrimitives()) {
                    ImGui::Text("Primitive %u", primitiveCounter);
                    ImGui::Text("Origin: %.2f %.2f %.2f", primitive->getOriginPoint().x, primitive->getOriginPoint().y,
                                primitive->getOriginPoint().z);
                    ImGui::Separator();
                    primitiveCounter++;
                }
                ImGui::End();
            }

            _window.clear();
            ImGui::SFML::Render(_window);
            _window.display();
        }
        camera->awaitDrawImage();
    }
} // namespace rt
