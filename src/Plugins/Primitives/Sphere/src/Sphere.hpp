/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "../../APrimitive.hpp"

namespace rt
{
    class Sphere final : public APrimitive {
    private:
        float _radius = 0.5;

    public:
        class SphereException final : public APrimitiveException {
        public:
            SphereException(const std::string &message) : APrimitiveException("Sphere", message) {}
        };

        Sphere(const std::vector<math::Vector3<float>> &vertices) : APrimitive(vertices) {}

        [[nodiscard]] float hit(const math::Ray &ray) const override;
        [[nodiscard]] math::Vector3<float> getNormal(const math::Vector3<float> &point) const override;

        [[nodiscard]] float getRadius() const { return _radius; }
        void setRadius(const float radius) { _radius = radius; }
    };
} // namespace rt

extern "C" {
    rt::IPrimitive *createComponent(const libconfig::Setting &setting, rt::IMaterial *material)
    {
        auto *ptr = new rt::Sphere(
            std::vector{math::Vector3{setting["origin"]["x"].operator float(), setting["origin"]["y"].operator float(),
                                      setting["origin"]["z"].operator float()}});

        ptr->setRadius(setting["radius"].operator float());

        ptr->settingsTransform(setting);
        ptr->setMaterial(material);

        return ptr;
    }
}

#endif // SPHERE_HPP
