/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Main
*/

#include <libconfig.h++>

#include "Raytracer.hpp"
#include "Parser/Parser.hpp"

// #include "../../Plugins/Lights/ILight.hpp"

int main([[maybe_unused]] int ac, char **av)
{
    rt::Parser parser;
    parser.parseScene(av[1]);
    // parser.getCamera()->generateImage(parser.getPrimitives());

    // exit(0);

    // rt::Raytracer raytracer;

    // try {
    //     raytracer.run();
    // } catch (const rt::Raytracer::RaytracerException &e) {
    //     std::cerr << e.what() << std::endl;
    //     return 84;
    // }
    // return 0;
}
