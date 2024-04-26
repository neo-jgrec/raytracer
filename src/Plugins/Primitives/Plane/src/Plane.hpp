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
            math::Vector3<float> _position = {0, 0, 0}; // Top left
            math::Vector3<float> _limit = {0, 0, 0}; // Bottom right
        public:
            class PlaneException final : public APrimitiveException {
            public:
                PlaneException(const std::string &message) :
                    APrimitiveException("Plane", message) {}
            };

            [[nodiscard]] float hit(const math::Ray &ray) const override;

            [[nodiscard]] math::Vector3<float> getPosition() const;
            [[nodiscard]] math::Vector3<float> getLimit() const;

            void setPosition(const math::Vector3<float> &position);
            void setLimit(const math::Vector3<float> &limit);
        };
} // namespace rt

extern "C" {
    rt::IPrimitive *createComponent(libconfig::Setting &plane, rt::IMaterial *material)
    {
        auto *newPlane = new rt::Plane();
        newPlane->setPosition(math::Vector3{
            static_cast<float>(plane["x"].operator int()),
            static_cast<float>(plane["y"].operator int()),
            static_cast<float>(plane["z"].operator int())
        });
        newPlane->setLimit(math::Vector3{
            static_cast<float>(plane["limit"]["x"].operator int()),
            static_cast<float>(plane["limit"]["y"].operator int()),
            static_cast<float>(plane["limit"]["z"].operator int())
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
