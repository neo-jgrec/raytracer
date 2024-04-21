/*
** EPITECH PROJECT, 2024
** BS-Raytracer
** File description:
** Raytracer
*/

#include "Raytracer.hpp"

#include <list>

#include "../Utils/Utils.hpp"
#include "../Cameras/ICamera.hpp"

namespace rt
{
    void Raytracer::run()
    {
        std::list<utils::DLLoader<IPrimitive>> loadersPrimitives;
        std::list<utils::DLLoader<IMaterial>> loadersMaterials;
        std::list<IPrimitive *> primitives;

        for (const auto &path : {
                 "./bin/lib/raytracer_sphere.so",
             }) {
            loadersPrimitives.emplace_back(utils::PRIMITIVE, path);
            loadersMaterials.emplace_back(utils::MATERIAL, "./bin/lib/raytracer_flatcolor.so");
            loadersPrimitives.back().get()->setMaterial(loadersMaterials.back().get());
            primitives.push_back(loadersPrimitives.back().get());
        }

        const utils::DLLoader<ICamera> camera{utils::CAMERA, "./bin/lib/raytracer_camera.so"};
        camera.get()->generateImage(primitives);
    }
}
