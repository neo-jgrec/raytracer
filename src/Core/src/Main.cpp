/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Main
*/

#include <iostream>

#include "Raytracer.hpp"

int main()
{
    rt::Raytracer raytracer;

    try {
        raytracer.run();
    } catch (const rt::Raytracer::RaytracerException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
