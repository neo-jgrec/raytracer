/*
** EPITECH PROJECT, 2024
** BS-Raytracer
** File description:
** Raytracer
*/

#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include "Parser/Parser.hpp"

namespace rt
{
    class Raytracer {
    private:
        std::string _sceneName;
        std::string _saveAs;
        std::string _graphicalPlugin;
        Parser _parser;

        void toPPM(const std::string &filename);
        void toGraphical();

    public:
        class RaytracerException final : public utils::Exception {
        public:
            RaytracerException(const std::string &message) : Exception("Raytracer", message) {}
        };

        Raytracer(std::string sceneName, std::string saveAs = "", std::string graphicalPlugin = "");

        void run();
    };
} // namespace rt

#endif // RAYTRACER_HPP
