/*
** EPITECH PROJECT, 2024
** BS-Raytracer
** File description:
** Raytracer
*/

#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include "../Utils/Utils.hpp"

namespace rt
{
    class Raytracer {
    private:
        std::string _sceneName;

    public:
        class RaytracerException final : public utils::Exception {
        public:
            RaytracerException(const std::string &message) :
                Exception("Raytracer", message) {}
        };

        Raytracer(std::string sceneName);

        void run() const;
    };
}

#endif //RAYTRACER_HPP
