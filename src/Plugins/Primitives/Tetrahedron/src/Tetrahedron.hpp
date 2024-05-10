/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Tetrahedron
*/

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <libconfig.h++>
#include "../../APrimitive.hpp"

namespace rt
{
    class Tetrahedron final : public APrimitive {
    public:
        class TriangleException final : public APrimitiveException {
        public:
            TriangleException(const std::string &message) : APrimitiveException("Tetrahedron", message) {}
        };

        Tetrahedron() = delete;
        Tetrahedron(const std::vector<math::Vector3<float>> &vertices) : APrimitive(vertices) {}

        [[nodiscard]] float hit(const math::Ray &ray) const override;
        [[nodiscard]] math::Vector3<float> getNormal(const math::Vector3<float> &point) const override;
    };
} // namespace rt

extern "C" {
    rt::IPrimitive *createComponent(const libconfig::Setting &setting, rt::IMaterial *material)
    {
        auto *ptr = new rt::Tetrahedron(
            std::vector{math::Vector3{setting["v0"]["x"].operator float(), setting["v0"]["y"].operator float(),
                                      setting["v0"]["z"].operator float()},
                        math::Vector3{setting["v1"]["x"].operator float(), setting["v1"]["y"].operator float(),
                                      setting["v1"]["z"].operator float()},
                        math::Vector3{setting["v2"]["x"].operator float(), setting["v2"]["y"].operator float(),
                                      setting["v2"]["z"].operator float()},
                        math::Vector3{setting["v3"]["x"].operator float(), setting["v3"]["y"].operator float(),
                                      setting["v3"]["z"].operator float()}});

        ptr->settingsTransform(setting);
        ptr->setMaterial(material);

        return ptr;
    }
}

#endif // SPHERE_HPP
