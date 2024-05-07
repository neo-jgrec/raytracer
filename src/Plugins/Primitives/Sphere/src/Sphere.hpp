/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#ifndef SPHERE_HPP
#define SPHERE_HPP

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
            SphereException(const std::string &message) : APrimitiveException("Sphere", message) {}
        };

        [[nodiscard]] float hit(const math::Ray &ray) const override;
        [[nodiscard]] math::Vector3<float> getNormal(const math::Vector3<float> &point) const override;

        [[nodiscard]] const math::Vector3<float> &getOrigin() const { return _origin; }
        [[nodiscard]] float getRadius() const { return _radius; }

        void setOrigin(const math::Vector3<float> &origin) { _origin = origin; }
        void setRadius(const float radius) { _radius = radius; }
    };
} // namespace rt

extern "C" {
    rt::IPrimitive *createComponent(libconfig::Setting &sphere, rt::IMaterial *material)
    {
        auto *newSphere = new rt::Sphere();

        newSphere->setOrigin(math::Vector3{static_cast<float>(sphere["x"].operator int()),
                                           static_cast<float>(sphere["y"].operator int()),
                                           static_cast<float>(sphere["z"].operator int())});
        newSphere->setRadius((sphere["r"].operator float()));
        newSphere->setMaterial(material);

        return newSphere;
    }

    void destroy(const rt::IPrimitive *ptr) { delete ptr; }
}

#endif // SPHERE_HPP
