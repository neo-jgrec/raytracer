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
        math::Vector3<float> _origin;
        math::Vector3<float> _direction;

    public:
        class PlaneException final : public APrimitiveException {
        public:
            PlaneException(const std::string &message) : APrimitiveException("Plane", message) {}
        };

        [[nodiscard]] float hit(const math::Ray &ray) const override;
        [[nodiscard]] math::Vector3<float> getNormal(const math::Vector3<float> &point) const override;

        [[nodiscard]] math::Vector3<float> getOrigin() const { return _origin; }
        [[nodiscard]] math::Vector3<float> getDirection() const { return _direction; }

        void setOrigin(const math::Vector3<float> &origin) { _origin = origin; }
        void setDirection(const math::Vector3<float> &direction) { _direction = direction; }
        void setTranslation(const math::Vector3<float> &translation) override { _origin += translation; }
    };
} // namespace rt

extern "C" {
    rt::IPrimitive *createComponent(const libconfig::Setting &setting, rt::IMaterial *material)
    {
        auto *plane = new rt::Plane();

        plane->setOrigin({static_cast<float>(setting["origin"]["x"].operator int()),
                          static_cast<float>(setting["origin"]["y"].operator int()),
                          static_cast<float>(setting["origin"]["z"].operator int())});
        plane->setDirection({static_cast<float>(setting["direction"]["x"].operator int()),
                             static_cast<float>(setting["direction"]["y"].operator int()),
                             static_cast<float>(setting["direction"]["z"].operator int())});
        plane->setMaterial(material);

        return plane;
    }

    void destroy(const rt::IPrimitive *ptr) { delete ptr; }
}

#endif /* !PLANE_HPP */
