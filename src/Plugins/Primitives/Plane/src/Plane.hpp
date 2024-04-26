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
    class Plane : public APrimitive {
        private:
            math::Vector3<float> _origin = {0, 0, 0};
            math::Vector3<float> _direction = {0, 0, 0};
        public:
            class PlaneException final : public APrimitiveException {
            public:
                PlaneException(const std::string &message) :
                    APrimitiveException("Plane", message) {}
            };

            [[nodiscard]] float hit(const math::Ray &ray) const override;

            [[nodiscard]] math::Vector3<float> getOrigin() const;
            [[nodiscard]] math::Vector3<float> getDirection() const;

            void setOrigin(const math::Vector3<float> &origin);
            void setDirection(const math::Vector3<float> &direction);
        };
} // namespace rt

extern "C" {
    rt::IPrimitive *createComponent(libconfig::Setting &plane, rt::IMaterial *material)
    {
        auto *newPlane = new rt::Plane();
        newPlane->setOrigin(math::Vector3{
            static_cast<float>(plane["origin"]["x"].operator int()),
            static_cast<float>(plane["origin"]["y"].operator int()),
            static_cast<float>(plane["origin"]["z"].operator int())
        });
        newPlane->setDirection(math::Vector3{
            static_cast<float>(plane["direction"]["x"].operator int()),
            static_cast<float>(plane["direction"]["y"].operator int()),
            static_cast<float>(plane["direction"]["z"].operator int())
        });
        newPlane->setMaterial(material);
        return newPlane;
    }

    void destroy(const rt::IPrimitive *ptr)
    {
        delete ptr;
    }
}

#endif /* !PLANE_HPP */
