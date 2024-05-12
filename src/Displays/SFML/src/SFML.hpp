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
        static void waitThreads(std::vector<std::thread> &threads);

    public:
        SFML(uint32_t width = 800, uint32_t height = 600, const std::string &title = "Raytracer");
        ~SFML() override;

        void run(std::shared_ptr<Scene> parser) override;
    };
} // namespace rt

extern "C" {
    rt::IDisplay *create_display(const uint32_t width, const uint32_t height, const std::string &title)
    {
        return new rt::SFML(width, height, title);
    }

    void destroy(const rt::SFML *display) { delete display; }
}

#endif /* !SFML_HPP_ */
