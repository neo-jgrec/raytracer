/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Triangle
*/

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "../../APrimitive.hpp"

namespace rt
{
    class Triangle final : public APrimitive {
    public:
        class TriangleException final : public APrimitiveException {
        public:
            TriangleException(const std::string &message) : APrimitiveException("Triangle", message) {}
        };

        Triangle(const std::vector<math::Vector3<float>> &vertices) : APrimitive(vertices) {}

        [[nodiscard]] float hit(const math::Ray &ray) const override;
        [[nodiscard]] math::Vector3<float> getNormal(const math::Vector3<float> &point) const override;
    };
} // namespace rt

extern "C" {
    rt::IPrimitive *createComponent(const libconfig::Setting &setting, rt::IMaterial *material)
    {
        auto *ptr = new rt::Triangle(
            std::vector{math::Vector3{setting["v0"]["x"].operator float(), setting["v0"]["y"].operator float(),
                                      setting["v0"]["z"].operator float()},
                        math::Vector3{setting["v1"]["x"].operator float(), setting["v1"]["y"].operator float(),
                                      setting["v1"]["z"].operator float()},
                        math::Vector3{setting["v2"]["x"].operator float(), setting["v2"]["y"].operator float(),
                                      setting["v2"]["z"].operator float()}});

        ptr->settingsTransform(setting);
        ptr->setMaterial(material);

        return ptr;
    }
}

#endif // SPHERE_HPP
