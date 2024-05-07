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
#include "../Utils/DLLoader.hpp"
#include "Parser/Parser.hpp"

namespace rt
{
    void Raytracer::toPPM(const std::string &filename)
    {
        const auto image =
            _parser->getCamera()->generateImage(_parser->getPrimitives(), _parser->getLights(), false, true);

        std::ofstream file(filename);
        file << "P6\n" << std::get<0>(image) << " " << std::get<1>(image) << "\n255\n";
        file.write(reinterpret_cast<const char *>(std::get<2>(image).get()),
                   std::get<0>(image) * std::get<1>(image) * 3);
        file.close();
        std::cout << "Image saved to " << filename << std::endl;
    }
    void Raytracer::toGraphical()
    {
        const utils::DLLoader<IDisplay> graphicalPluginLoader(_graphicalPlugin, "create_display");
        const std::function create_display =
            reinterpret_cast<IDisplay *(*)(uint32_t, uint32_t, const std::string &)>(graphicalPluginLoader.get());

        const auto [width, height] = _parser->getCamera()->getResolution();
        const std::unique_ptr<IDisplay> display(create_display(width, height, "Raytracer"));
        display->run(_parser);
    }


    Raytracer::Raytracer(std::string sceneName, std::string saveAs, std::string graphicalPlugin) :
        _sceneName(std::move(sceneName)), _saveAs(std::move(saveAs)), _graphicalPlugin(std::move(graphicalPlugin))
    {
        if (_sceneName.empty())
            throw RaytracerException("No scene provided");
        if (_saveAs.empty() && _graphicalPlugin.empty())
            throw RaytracerException("No output provided");
    }

    void Raytracer::run()
    {
        try {
            _parser = std::make_shared<Parser>(_sceneName);
        } catch (const Parser::ParserExecption &e) {
            throw RaytracerException(e.what());
        }

        if (!_saveAs.empty()) {
            try {
                toPPM(_saveAs);
            } catch (const RaytracerException &e) {
                throw RaytracerException(e.what());
            }
        }
        if (!_graphicalPlugin.empty()) {
            try {
                toGraphical();
            } catch (const utils::DLLoader<IDisplay>::DLLoaderException &e) {
                throw RaytracerException(e.what());
            } catch (const IDisplay::IDisplayException &e) {
                throw RaytracerException(e.what());
            }
        }
    }
} // namespace rt
