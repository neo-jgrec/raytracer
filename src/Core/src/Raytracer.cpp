/*
** EPITECH PROJECT, 2024
** BS-Raytracer
** File description:
** Raytracer
*/

#include "Raytracer.hpp"

#include <fstream>
#include <functional>
#include <iostream>
#include <utility>

#include "../Displays/IDisplay.hpp"
#include "Parser/Parser.hpp"
#include "../Utils/DLLoader.hpp"

namespace rt
{
    Raytracer::Raytracer(std::string sceneName, std::string graphicalPlugin /*= ""*/)
        : _sceneName(std::move(sceneName)), _graphicalPlugin(std::move(graphicalPlugin))
    {}

    void Raytracer::run() const
    {

        Parser parser;
        try {
            parser.parseScene(_sceneName);
        } catch (const Parser::ParserExecption &e) {
            std::cerr << e.what() << std::endl;
            return;
        }

        const auto image = parser.getCamera()->generateImage(parser.getPrimitives(), parser.getLights());
        const std::string imageName{"image.out.ppm"};

        utils::DLLoader<rt::IDisplay> graphicalPluginLoader(_graphicalPlugin, "create_display");
        const std::function create_display = reinterpret_cast<rt::IDisplay *(*)()>(graphicalPluginLoader.get());

        if (create_display == nullptr) {
            std::cerr << "Failed to load graphical plugin" << std::endl;
            return;
        }

        rt::IDisplay *display = create_display();
        display->createWindow(std::get<0>(image), std::get<1>(image), "Raytracer");
        display->run(parser);
        display->destroyWindow();

        std::ofstream file(imageName);
        file << "P6\n" << std::get<0>(image) << " " << std::get<1>(image) << "\n255\n";
        file.write(reinterpret_cast<const char *>(std::get<2>(image).get()),
                   std::get<0>(image) * std::get<1>(image) * 3);
        file.close();
        std::cout << "Image saved to " << imageName << std::endl;
    }
} // namespace rt
