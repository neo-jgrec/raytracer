/*
** EPITECH PROJECT, 2024
** BS-Raytracer
** File description:
** Raytracer
*/

#include "Raytracer.hpp"

#include <fstream>
#include <iostream>
#include <utility>
#include <map>

#include "../Cameras/ICamera.hpp"
#include "Parser/Parser.hpp"

namespace rt
{
    Raytracer::Raytracer(std::string sceneName) :
        _sceneName(std::move(sceneName))
    {}

    void Raytracer::run() const
    {
        Parser parser;
        parser.parseScene(_sceneName);

        const auto image = parser.getCamera()->generateImage(parser.getPrimitives(), parser.getLights());
        const std::string imageName{"image.out.ppm"};

        std::ofstream file(imageName);
        file << "P6\n" << std::get<0>(image) << " " << std::get<1>(image) << "\n255\n";
        file.write(reinterpret_cast<const char *>
                   (std::get<2>(image).get()), std::get<0>(image) * std::get<1>(image) * 3);
        file.close();
        std::cout << "Image saved to " << imageName << std::endl;
    }
}
