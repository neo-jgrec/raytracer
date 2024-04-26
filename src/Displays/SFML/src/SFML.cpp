/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SFML
*/

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML.hpp"



rt::SFML::SFML() = default;

rt::SFML::~SFML() {}

void rt::SFML::createWindow(const int &width, const int &height, const std::string &title)
{
    _window.create(sf::VideoMode(width, height), title);
    _window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(_window)) {
        throw std::runtime_error("Failed to initialize ImGui-SFML");
    }
}

void rt::SFML::destroyWindow()
{
    _window.close();
    ImGui::SFML::Shutdown();
}

void rt::SFML::run(const rt::Parser &parser)
{
    sf::Clock deltaClock;
    while (_window.isOpen()) {
        sf::Event event{};
        while (_window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(_window, event);

            if (event.type == sf::Event::Closed) {
                _window.close();
            }
        }

        const math::Vector3<float>& cameraOrigin = parser.getCamera()->getOrigin();
        sf::Vector3f cameraPosition(cameraOrigin.x, cameraOrigin.y, cameraOrigin.z);
        sf::View view;

        ImGui::SFML::Update(_window, deltaClock.restart());

        ImGui::Begin("Super Raytracer");
        ImGui::Text("Hello, world!");
        ImGui::End();

        _window.clear();
        ImGui::SFML::Render(_window);
        _window.display();
    }

    ImGui::SFML::Shutdown();
}
