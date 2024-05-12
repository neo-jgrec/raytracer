/*
** EPITECH PROJECT, 2024
** BS-Raytracer
** File description:
** Raytracer
*/

#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include <memory>
#include "Scene/Scene.hpp"

namespace rt
{
    class Raytracer {
    private:
        std::string _sceneName;
        std::string _saveAs;
        std::string _graphicalPlugin;
        std::shared_ptr<Scene> _parser;
        bool _preview = false;

        void toPPM(const std::string &filename);
        void toGraphical();

    public:
        class RaytracerException final : public utils::Exception {
        public:
            RaytracerException(const std::string &message) : Exception("Raytracer", message) {}
        };

        Raytracer(std::string sceneName, std::string saveAs = "", std::string graphicalPlugin = "",
                  bool preview = false);

        void run();
    };
} // namespace rt

#endif // RAYTRACER_HPP
