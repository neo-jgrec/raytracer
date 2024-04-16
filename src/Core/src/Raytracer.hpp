/*
** EPITECH PROJECT, 2024
** BS-Raytracer
** File description:
** Raytracer
*/

#ifndef RAYTRACER_HPP
    #define RAYTRACER_HPP

    #include <SFML/Graphics.hpp>

class Raytracer {
private:
    sf::RenderWindow _window;

    void event();
    void draw();

public:
    Raytracer();
    ~Raytracer();

    void run();
};

#endif //RAYTRACER_HPP
