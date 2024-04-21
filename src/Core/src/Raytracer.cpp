/*
** EPITECH PROJECT, 2024
** BS-Raytracer
** File description:
** Raytracer
*/

#include "Raytracer.hpp"

#include <list>

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
            try {
                loadersPrimitives.emplace_back(utils::PRIMITIVE, path);
                loadersMaterials.emplace_back(utils::MATERIAL, "./bin/lib/raytracer_uvcolor.so");
                loadersPrimitives.back().get()->setMaterial(loadersMaterials.back().get());
            } catch (const utils::Exception &e) {
                std::cerr << e.what() << std::endl;
                continue;
            }

            primitives.push_back(loadersPrimitives.back().get());
        }

        const utils::DLLoader<ICamera> camera{utils::CAMERA, "./bin/lib/raytracer_camera.so"};
        camera.get()->generateImage(primitives);
    }
}
