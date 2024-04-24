/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Main
*/

#include <libconfig.h++>
#include <iostream>

#include "Raytracer.hpp"
#include "Parser/Parser.hpp"

#include "../../Cameras/ICamera.hpp"
#include "../../Plugins/Primitives/IPrimitive.hpp"
#include "../../Plugins/Materials/IMaterial.hpp"
// #include "../../Plugins/Lights/ILight.hpp"

int main([[maybe_unused]] int ac, char **av)
{
    std::list<utils::DLLoader<rt::ICamera>> cameraLoaders;
    std::list<utils::DLLoader<rt::IPrimitive>> primitiveLoaders;
    std::map<std::string, utils::DLLoader<rt::IMaterial>> materialLoaders;

    rt::Parser parser(cameraLoaders, primitiveLoaders, materialLoaders);
    parser.parseScene(av[1]);
    parser.getCamera()->generateImage(parser.getPrimitives());

    for (auto &loader : cameraLoaders)
        loader.destroy();
    for (auto &loader : primitiveLoaders)
        loader.destroy();
    for (auto &loader : materialLoaders)
        loader.second.destroy();

    exit(0);

    rt::Raytracer raytracer;

    try {
        raytracer.run();
    } catch (const rt::Raytracer::RaytracerException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
