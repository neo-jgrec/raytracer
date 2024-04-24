/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Main
*/

#include <iostream>

#include "Raytracer.hpp"

int main(const int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " scene.cfg" << std::endl;
        return 84;
    }

    try {
        const rt::Raytracer raytracer(av[1]);
        raytracer.run();
    } catch (const rt::Raytracer::RaytracerException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
