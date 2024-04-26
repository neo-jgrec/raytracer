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
        if (!ImGui::SFML::Init(_window)) {
            throw std::runtime_error("Failed to initialize ImGui-SFML");
        }
    }

    SFML::~SFML()
    {
        _window.close();
        ImGui::SFML::Shutdown();
    }

    void SFML::run(Parser &parser)
    {
        const auto image = parser.getCamera()->generateImage(parser.getPrimitives(), parser.getLights(), true);

        sf::Texture texture;
        texture.create(std::get<0>(image), std::get<1>(image));
        texture.update(std::get<2>(image).get());
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

            ImGui::Begin("Super Raytracer");
            ImGui::Text("Hello, world!");
            ImGui::End();

            _window.clear();
            ImGui::SFML::Render(_window);
            parser.getCamera()->generateImage(parser.getPrimitives(), parser.getLights(), true);
            _window.draw(sprite);
            _window.display();
        }

        ImGui::SFML::Shutdown();
    }
} // namespace rt
