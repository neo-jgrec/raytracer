/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Plane
*/

#ifndef PLANE_HPP
#define PLANE_HPP

#include <libconfig.h++>
#include "../../APrimitive.hpp"

namespace rt
{
    class Plane final : public APrimitive {
    private:
        math::Vector3<float> _direction;

    public:
        class PlaneException final : public APrimitiveException {
        public:
            PlaneException(const std::string &message) : APrimitiveException("Plane", message) {}
        };

        Plane(const std::vector<math::Vector3<float>> &vertices) : APrimitive(vertices) {}

        [[nodiscard]] float hit(const math::Ray &ray) const override;
        [[nodiscard]] math::Vector3<float> getNormal(const math::Vector3<float> &point) const override;

        [[nodiscard]] math::Vector3<float> getDirection() const { return _direction; }
        void setDirection(const math::Vector3<float> &direction) { _direction = direction; }
    };
} // namespace rt

extern "C" {
    rt::IPrimitive *createComponent(const libconfig::Setting &setting, rt::IMaterial *material)
    {
        auto *ptr = new rt::Plane(
            std::vector{math::Vector3{setting["origin"]["x"].operator float(), setting["origin"]["y"].operator float(),
                                      setting["origin"]["z"].operator float()}});

        ptr->setDirection(math::Vector3{setting["direction"]["x"].operator float(),
                                        setting["direction"]["y"].operator float(),
                                        setting["direction"]["z"].operator float()});

        ptr->settingsTransform(setting);
        ptr->setMaterial(material);

        return ptr;
    }
}

#endif /* !PLANE_HPP */
