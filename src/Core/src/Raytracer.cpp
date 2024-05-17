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

#include "../Plugins/Displays/IDisplay.hpp"
#include "../Utils/DLLoader.hpp"
#include "Scene/Scene.hpp"

#include "Images/Images.hpp"

namespace rt
{
    void Raytracer::toPPM(const std::string &filename) const
    {
        ImageRGB image(_parser->getCamera()->getResolution());
        _parser->getCamera()->drawImage(_parser->getPrimitives(), _parser->getLights(), image);

        std::ofstream file(filename);

        file << "P6\n" << image.getSize().first << " " << image.getSize().second << "\n255\n";
        file.write(reinterpret_cast<const char *>(image.getPixels().get()),
                   image.getSize().first * image.getSize().second * 3);
        file.close();
    }
    void Raytracer::toGraphical() const
    {
        const utils::DLLoader<IDisplay> graphicalPluginLoader(_graphicalPlugin, "create_display");
        const std::function create_display =
            reinterpret_cast<IDisplay *(*)(uint32_t, uint32_t, const std::string &)>(graphicalPluginLoader.get());

        const auto [width, height] = _parser->getCamera()->getResolution();
        const std::unique_ptr<IDisplay> display(create_display(width, height, "Raytracer"));
        display->run(_parser);
    }


    Raytracer::Raytracer(std::string sceneName, std::string saveAs, std::string graphicalPlugin, const bool preview) :
        _sceneName(std::move(sceneName)), _saveAs(std::move(saveAs)), _graphicalPlugin(std::move(graphicalPlugin)),
        _preview(preview)
    {
        if (_sceneName.empty())
            throw RaytracerException("No scene provided");
        if (_saveAs.empty() && _graphicalPlugin.empty())
            throw RaytracerException("No output provided");
    }

    void Raytracer::run()
    {
        std::cout << "Loading scene " << _sceneName << std::endl;
        try {
            _parser = std::make_shared<Scene>(_sceneName);
        } catch (const Scene::ParserExecption &e) {
            throw RaytracerException(e.what());
        }
        if (_parser->getCamera() == nullptr)
            throw RaytracerException("No camera found in the scene");
        std::cout << "Scene parsed successfully" << std::endl;

        if (_preview) {
            ICamera *camera = _parser->getCamera();

            if (const auto [width, height] = camera->getResolution(); width < 400)
                camera->setResolution(width, height);
            else
                camera->setResolution(400, 400 * height / width);

            std::cout << "Previewing enabled, resolution set to 400x" << camera->getResolution().second << std::endl;
        }

        if (!_saveAs.empty()) {
            try {
                toPPM(_saveAs);
                std::cout << "Image saved to " << _saveAs << std::endl;
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
