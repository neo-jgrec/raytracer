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
            std::string _axis;
            float _position;
        public:
            class PlaneException final : public APrimitiveException {
            public:
                PlaneException(const std::string &message) :
                    APrimitiveException("Plane", message) {}
            };

            [[nodiscard]] float hit(const math::Ray &ray) const override;

            [[nodiscard]] const std::string getAxis() const;
            [[nodiscard]] float getPosition() const;

            void setAxis(const std::string axis);
            void setPosition(const float radius);
        };
} // namespace rt

extern "C" {
    rt::IPrimitive *createComponent(libconfig::Setting &plane, rt::IMaterial *material)
    {
        auto *newPlane = new rt::Plane();
        newPlane->setAxis((plane["axis"].operator std::string()));
        newPlane->setPosition(static_cast<float>(plane["position"].operator int()));
        newPlane->setMaterial(material);
        return newPlane;
    }

    void destroy(const rt::IPrimitive *ptr)
    {
        delete ptr;
    }
}

#endif /* !PLANE_HPP */
