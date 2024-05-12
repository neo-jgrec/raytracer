/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include <libconfig.h++>

#include "../../APrimitive.hpp"

namespace rt
{
    class Cylinder final : public APrimitive {
    private:
        float _radius = 0.5;
        float _height = 1;

    public:
        class CylinderException final : public APrimitiveException {
        public:
            CylinderException(const std::string &message) : APrimitiveException("Cylinder", message) {}
        };

        Cylinder(const std::vector<math::Vector3<float>> &vertices,
                 const std::vector<math::Vector3<float>> &directions) :
            APrimitive(vertices, directions)
        {}

        [[nodiscard]] float hit(const math::Ray &ray) const override;
        [[nodiscard]] math::Vector3<float> getNormal(const math::Vector3<float> &point) const override;

        void setRadius(const float radius) { _radius = radius; }
        [[nodiscard]] float getRadius() const { return _radius; }

        void setHeight(const float height) { _height = height; }
        [[nodiscard]] float getHeight() const { return _height; }
    };
} // namespace rt

extern "C" {
    rt::IPrimitive *createComponent(const libconfig::Setting &setting, rt::IMaterial *material)
    {
        auto *ptr = new rt::Cylinder(
            std::vector{math::Vector3{setting["origin"]["x"].operator float(), setting["origin"]["y"].operator float(),
                                      setting["origin"]["z"].operator float()}},
            std::vector{math::Vector3{setting["direction"]["x"].operator float(),
                                      setting["direction"]["y"].operator float(),
                                      setting["direction"]["z"].operator float()}});

        ptr->setRadius(setting["radius"].operator float());
        ptr->setHeight(setting["height"].operator float());

        ptr->settingsTransform(setting);
        ptr->setMaterial(material);

        return ptr;
    }
}

#endif // CYLINDER_HPP
