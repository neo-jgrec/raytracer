/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <iostream>
#include <libconfig.h++>
#include "../../APrimitive.hpp"

namespace rt
{
    class Sphere final : public APrimitive {
    private:
        math::Vector3<float> _origin = math::Vector3<float>{0, 0, -1};
        float _radius = 0.5;

    public:
        class SphereException final : public APrimitiveException {
        public:
            SphereException(const std::string &message) :
                APrimitiveException("Sphere", message) {}
        };

        [[nodiscard]] float hit(const math::Ray &ray) const override;

        void setOrigin(const math::Vector3<float> &origin);
        void setRadius(float radius);
    };
} // namespace rt

extern "C" {
    rt::IPrimitive *createComponent(libconfig::Setting &sphere, rt::IMaterial *material) {
        auto *newSphere = new rt::Sphere();

        newSphere->setOrigin(math::Vector3<float>{
            static_cast<float>(sphere["x"].operator int()),
            static_cast<float>(sphere["y"].operator int()),
            static_cast<float>(sphere["z"].operator int())
        });
        newSphere->setRadius(static_cast<float>(sphere["r"].operator int()));

        newSphere->setMaterial(material);

        return newSphere;
    }

    void destroy(const rt::IPrimitive *ptr) {
        delete ptr;
    }
}

#endif //SPHERE_HPP
