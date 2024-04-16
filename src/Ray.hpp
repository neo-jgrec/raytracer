/*
** EPITECH PROJECT, 2024
** BS-Raytracer
** File description:
** Ray
*/

#ifndef RAY_HPP
    #define RAY_HPP

    #include <SFML/System/Vector3.hpp>

class Ray {
public:
    sf::Vector3f origin;
    sf::Vector3f direction;

    Ray(sf::Vector3f origin = {0, 0, 0}, sf::Vector3f direction = {0, 0, 0})
        : origin(origin), direction(direction)
    {};
};

#endif //RAY_HPP
