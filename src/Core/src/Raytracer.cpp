/*
** EPITECH PROJECT, 2024
** BS-Raytracer
** File description:
** Raytracer
*/

#include "Raytracer.hpp"

#include <iostream>

Raytracer::Raytracer()
    : _window(sf::VideoMode(800, 600), "Raytracer", sf::Style::Close | sf::Style::Titlebar)
{
    _window.setFramerateLimit(60);
}

Raytracer::~Raytracer()
{}

void Raytracer::event()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
    }
}

void Raytracer::draw()
{
    _window.clear();

    // Create a object
    // Use the camera to render the object

    _window.display();
}

void Raytracer::run()
{
    draw();
    while (_window.isOpen())
        event();
}
