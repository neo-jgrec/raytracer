/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SFML
*/

#include "SFML.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include "imgui-SFML.h"
#include "imgui.h"
#include "../../../Core/src/Scene/Scene.hpp"

namespace rt
{
    SFML::SFML(const uint32_t width, const uint32_t height, const std::string &title)
    {
        _window.create(sf::VideoMode(width, height), title);
        _window.setFramerateLimit(60);
        if (!ImGui::SFML::Init(_window)) {
            throw std::runtime_error("Failed to initialize ImGui-SFML");
        }
    }

    SFML::~SFML()
    {
        _window.close();
        ImGui::SFML::Shutdown();
    }

    void SFML::waitThreads(std::vector<std::thread> &threads)
    {
        for (auto &thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

    void SFML::run(std::shared_ptr<Scene> parser)
    {
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        auto image = parser->getCamera()->generateImage(parser->getPrimitives(), parser->getLights(), true);

        bool isSaving = false;
        bool isOpeningCfgFile = false;
        bool isPreviewing = false;
        static char filename[256] = {0};
        float zoomInImage = 0.5f;

        sf::Texture texture;
        parser->getCamera()->getMutex().lock();
        texture.create(std::get<0>(image), std::get<1>(image));
        texture.update(std::get<2>(image).get());
        parser->getCamera()->getMutex().unlock();
        sf::Sprite sprite(texture);

        sf::Clock deltaClock;
        while (_window.isOpen()) {
            sf::Event event{};
            while (_window.pollEvent(event)) {
                ImGui::SFML::ProcessEvent(_window, event);

                if (event.type == sf::Event::Closed) {
                    _window.close();
                }
            }
            ImGui::SFML::Update(_window, deltaClock.restart());

            ImGui::BeginMainMenuBar();
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Save image as")) {
                    isSaving = true;
                }
                if (ImGui::MenuItem("Open cfg file")) {
                    isOpeningCfgFile = true;
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Quit")) {
                    _window.close();
                }
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
                if (ImGui::Button("Save")) {
                    texture.copyToImage().saveToFile(filename);
                    isSaving = false;
                }
                ImGui::SameLine();
                if (ImGui::Button("Close")) {
                    isSaving = false;
                }
                ImGui::End();
            }

            if (isOpeningCfgFile) {
                ImGui::Begin("Open cfg file", &isOpeningCfgFile, ImGuiWindowFlags_NoCollapse);
                ImGui::InputText("Filename", filename, IM_ARRAYSIZE(filename));
                ImGui::Checkbox("Preview", &isPreviewing);
                ImGui::Text("Warning: This will close the current scene");
                if (ImGui::Button("Open")) {
                    try {
                        texture.create(1, 1);
                        sf::Uint8 black[4] = {0, 0, 0, 255};
                        texture.update(black);
                        parser = std::make_shared<Scene>(std::filesystem::absolute(filename).string());
                        if (isPreviewing) {
                            auto ratio = parser->getCamera()->getResolution().first / parser->getCamera()->getResolution().second;
                            parser->getCamera()->setResolution(400, 400 / ratio);
                            zoomInImage = 1.0f;
                        }
                        image = parser->getCamera()->generateImage(parser->getPrimitives(), parser->getLights(), true);
                        texture.create(std::get<0>(image), std::get<1>(image));
                        texture.update(std::get<2>(image).get());
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
            if (parser->getCamera() != nullptr) {
                parser->getCamera()->getMutex().lock();
                texture.update(std::get<2>(image).get());
                parser->getCamera()->getMutex().unlock();
            }
            ImGui::SliderFloat("Zoom", &zoomInImage, 0.1f, 2.0f);
            sprite.setScale(zoomInImage, zoomInImage);
            ImGui::Image(sprite);
            ImGui::End();

            ImGui::Begin("Camera");
            if (parser->getCamera()) {
                ImGui::Text("Camera origin: %f %f %f", parser->getCamera()->getOrigin().x, parser->getCamera()->getOrigin().y, parser->getCamera()->getOrigin().z);
                ImGui::Text("Camera resolution: %d %d", parser->getCamera()->getResolution().first, parser->getCamera()->getResolution().second);
            }
            ImGui::End();

            ImGui::Begin("Lights");
            if (!parser->getLights().empty()) {
                std::size_t lightCounter = 1;
                for (auto &light : parser->getLights()) {
                    ImGui::Text("Light %lu : (%f %f %f)", lightCounter, light->getOrigin().x, light->getOrigin().y, light->getOrigin().z);
                    ImGui::Separator();
                    lightCounter++;
                }
            }
            ImGui::End();

            ImGui::Begin("Primitives");
            if (!parser->getPrimitives().empty()) {
                std::size_t primitiveCounter = 1;
                for (auto &primitive : parser->getPrimitives()) {
                    ImGui::Text("Primitive %lu : (%f %f %f)", primitiveCounter, primitive->getOriginPoint().x, primitive->getOriginPoint().y, primitive->getOriginPoint().z);
                    ImGui::Separator();
                    primitiveCounter++;
                }
            }
            ImGui::End();

            _window.clear();
            ImGui::SFML::Render(_window);
            _window.display();
        }
        waitThreads(parser->getCamera()->getThreads());
    }
} // namespace rt
