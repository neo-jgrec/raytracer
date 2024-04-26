/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Main
*/

#include <getopt.h>
#include <iostream>

#include "Raytracer.hpp"


static void displayHelp(const std::string_view binaryName)
{
    std::cerr << "Usage: " << binaryName << " scene.cfg\n"
              << " -p, --ppm [output.ppm]              Save the scene to a PPM file\n"
                 " -d, --display [graphical_plugin.so] Display the scene using the graphical plugin\n"
                 " -h, --help                          Display this help message"
              << std::endl;
}

static bool handleOpt(const int ac, char **av)
{
    const auto shortOpt = "p:d:h";
    constexpr option longOpt[] = {{"ppm", required_argument, nullptr, 'p'},
                                  {"display", required_argument, nullptr, 'd'},
                                  {"help", no_argument, nullptr, 'h'},
                                  {nullptr, 0, nullptr, 0}};

    std::string saveAs;
    std::string displayLib;

    while (true) {
        const auto opt = getopt_long(ac, av, shortOpt, longOpt, nullptr);

        if (opt == -1)
            break;

        switch (opt) {
        case 'p':
            if (!saveAs.empty())
                return false;
            saveAs = optarg;
            break;
        case 'd':
            if (!displayLib.empty())
                return false;
            displayLib = optarg;
            break;
        case 'h':
            displayHelp(av[0]);
            break;
        default:
            displayHelp(av[0]);
            return false;
        }
    }

    if (optind != ac - 1)
        return false;

    try {
        rt::Raytracer raytracer(av[optind], saveAs, displayLib);
        raytracer.run();
    } catch (const rt::Raytracer::RaytracerException &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}

int main(const int ac, char **av)
{
    if (ac < 2) {
        displayHelp(av[0]);
        return 84;
    }

    return handleOpt(ac, av) ? 0 : 84;
}
