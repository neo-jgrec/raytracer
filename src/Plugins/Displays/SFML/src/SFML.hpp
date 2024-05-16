/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include <SFML/Graphics.hpp>

#include "../../IDisplay.hpp"

namespace rt
{
    class SFML final : public IDisplay {
    private:
        sf::RenderWindow _window;

    public:
        SFML(uint32_t width = 800, uint32_t height = 600, const std::string &title = "Raytracer");
        ~SFML() override;

        void run(std::shared_ptr<Scene> parser) override;
    };

    extern "C" {
        IDisplay *create_display(const uint32_t width, const uint32_t height, const std::string &title)
        {
            return new SFML{width, height, title};
        }

        void destroy(const SFML *display) { delete display; }
    }
} // namespace rt

#endif /* !SFML_HPP_ */
