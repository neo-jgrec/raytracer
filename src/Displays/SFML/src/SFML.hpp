/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "../../IDisplay.hpp"
#include <SFML/Graphics.hpp>

namespace rt {
    class SFML : public rt::IDisplay {
    public:
        SFML();
        ~SFML();

        void createWindow(const int &width, const int &height, const std::string &title) override;
        void destroyWindow() override;
        void run(const rt::Parser &parser) override;

    private:
        sf::RenderWindow _window;
    };
}

extern "C" {
    rt::IDisplay *create_display() {
        return new rt::SFML();
    }

    void destroy(rt::SFML *display) {
        delete display;
    }
}

#endif /* !SFML_HPP_ */
